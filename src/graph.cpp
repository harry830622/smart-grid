#include "graph.hpp"
#include "pseudo_vertex.hpp"
#include "switch.hpp"

#include "json.hpp"

#include <cassert>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
using json = nlohmann::json;

Graph::Graph(Grid* grid) : grid_(grid), root_(nullptr), wire_upgrade(0.0), switch_change(0)
{
}

void Graph::Print() const
{
  cout << "Graph: "<< endl;
  for (auto pair : vertices_) {
    pair.second->Print();
    cout << endl;
  }
  /*
     for (auto pair : edges_) {
     pair.second->Print();
     cout << endl;
     }
     */
}

void Graph::OutputJSON() const
{
  json j = {
    {"vertices", json::array({})},
    {"edges", json::array({})}
  };

  for (auto pair : vertices_) {
    j["vertices"].push_back({
        {"name", pair.second->GetRaw()->GetName()},
        {"x", pair.second->GetRaw()->GetCoordinate().GetX()},
        {"y", pair.second->GetRaw()->GetCoordinate().GetY()},
        {"z", pair.second->GetRaw()->GetCoordinate().GetZ()},
        {"source", pair.second->GetAssignSource()},
        });
  }

  for (auto pair : edges_) {
    j["edges"].push_back({
        {"name", pair.second->GetRaw()->GetName()},
        {"vertex1", pair.second->GetIncidentVertex(0)->GetRaw()->GetName()},
        {"vertex2", pair.second->GetIncidentVertex(1)->GetRaw()->GetName()}
        });
  }

  cout << j << endl;
}

Graph* Graph::Shrink()
{
  root_ = source_vertices_[0];

  MarkArticulationPoints();

  // Clean all the articulation points on the paths between every pair of source
  // vertices to ensure that all the source vertices will not be merged into
  // pseudo vertices.
  for (auto source_vertex : source_vertices_) {
    if (source_vertex != root_) {
      Vertex* vertex = source_vertex;
      while (vertex != root_) {
        assert(vertex != nullptr);

        vertex->SetIsArticulate(false);
        vertex = vertex->GetParent();
      }
    }
  }

  // Clean all the articulation points connecting to a resident directly to
  // avoid making useless pseudo vertices each containing just a single
  // resident.
  for (auto pair : vertices_) {
    Vertex* vertex = pair.second;

    for (int i = 0; i < vertex->GetIncidentEdgesNum(); ++i) {
      Vertex* neighbor = vertex->GetIncidentEdge(i)->GetNeighbor(vertex);

      if (neighbor->GetType() == Vertex::Type::RESIDENT) {
        vertex->SetIsArticulate(false);
        break;
      }
    }
  }

  Graph* tmp = ShrinkByArticulationPoints();

  Graph* shrinked_graph = tmp->ShrinkBySwitches();

  delete tmp;

  //shrinked_graph->Print();

  return shrinked_graph;
}

Vertex* Graph::GetVertex(string name) const
{
  if (vertices_.find(name) == vertices_.end()) {
    return nullptr;
  }

  return vertices_.find(name)->second;
}

int Graph::GetVerticesNum() const
{
  return vertices_.size();
}

Edge* Graph::GetEdge(string name) const
{
  if (edges_.find(name) == edges_.end()) {
    return nullptr;
  }

  return edges_.find(name)->second;
}

Vertex* Graph::GetRoot() const
{
  return root_;
}

void Graph::SetRoot(Vertex* root)
{
  root_ = root;
}

void Graph::AddVertex(Vertex* vertex)
{
  grid_->AddVertex(vertex);

  vertices_.insert(make_pair(vertex->GetRaw()->GetName(), vertex));

  if (vertex->GetType() == Vertex::Type::SOURCE) {
    source_vertices_.push_back(dynamic_cast<SourceVertex*>(vertex));
  }
}

void Graph::AddEdge(Edge* edge)
{
  grid_->AddEdge(edge);

  edges_.insert(make_pair(edge->GetRaw()->GetName(), edge));
}

void Graph::ResetVerticesMarks()
{
  for (auto pair : vertices_) {
    pair.second->ResetMarks();
  }
}

void FindArticulationPoints(Vertex* vertex, int depth)
{
  vertex->SetDepth(depth);
  vertex->SetLow(depth);

  for (int i = 0; i < vertex->GetIncidentEdgesNum(); ++i) {
    Vertex* child = vertex->GetIncidentEdge(i)->GetNeighbor(vertex);

    if (child != vertex->GetParent()) {
      if (!child->GetIsVisited()) {
        child->SetParent(vertex);
        vertex->AddChild(child);

        FindArticulationPoints(child, depth + 1);

        if (child->GetLow() >= vertex->GetDepth()) {
          vertex->SetIsArticulate(true);
          continue;
        }

        if (child->GetLow() < vertex->GetLow()) {
          vertex->SetLow(child->GetLow());
        }
      } else {
        if (child->GetDepth() < vertex->GetLow()) {
          vertex->SetLow(child->GetDepth());
        }
      }
    }
  }
}

void Graph::MarkArticulationPoints()
{
  ResetVerticesMarks();

  assert(root_ != nullptr);

  FindArticulationPoints(root_, 0);

  if (root_->GetChildrenNum() == 1) {
    root_->SetIsArticulate(false);
  }
}

Graph* Graph::ShrinkByArticulationPoints()
{
  Graph* shrinked_graph = new Graph(grid_);

  const string pseudo_vertex_prefix("PAV");
  int pseudo_vertex_counter = 0;

  ResetVerticesMarks();

  map<Vertex*, PseudoVertex*> pseudo_vertices;

  queue<Vertex*> bfs_queue;
  root_->SetIsVisted();
  bfs_queue.push(root_);
  while (!bfs_queue.empty()) {
    Vertex* front = bfs_queue.front();
    bfs_queue.pop();

    shrinked_graph->AddVertex(front);

    for (int i = 0; i < front->GetIncidentEdgesNum(); ++i) {
      Edge* incident_edge = front->GetIncidentEdge(i);
      Vertex* child = incident_edge->GetNeighbor(front);

      if (child != front->GetParent()) {
        if (!child->GetIsVisited()) {
          child->SetIsVisted();

          front->AddChild(child);
          child->SetParent(front);

          if (child->GetIsArticulate()) {
            const string pseudo_vertex_name(pseudo_vertex_prefix + to_string(pseudo_vertex_counter++));

            Node* new_node = new Node(pseudo_vertex_name);

            grid_->GetSmartGrid()->AddEquipment(new_node);

            PseudoVertex* pseudo_vertex = new PseudoVertex(new_node);

            Edge* new_edge = new Edge(incident_edge->GetRaw());

            pseudo_vertex->AddBoundaryVertex(new_edge, child);

            pseudo_vertex->AddIncidentEdge(new_edge);

            new_edge->AddIncidentVertex(front);
            new_edge->AddIncidentVertex(pseudo_vertex);

            front->SetIncidentEdge(i, new_edge);

            shrinked_graph->AddVertex(pseudo_vertex);
            shrinked_graph->AddEdge(new_edge);

            pseudo_vertices.insert(make_pair(child, pseudo_vertex));
          } else {
            bfs_queue.push(child);

            shrinked_graph->AddVertex(child);
            shrinked_graph->AddEdge(incident_edge);
          }
        } else {
          if (child->GetIsArticulate()) {
            assert(pseudo_vertices.count(child) == 1);

            PseudoVertex* pseudo_vertex = pseudo_vertices.find(child)->second;

            Edge* new_edge = new Edge(incident_edge->GetRaw());

            pseudo_vertex->AddBoundaryVertex(new_edge, child);

            pseudo_vertex->AddIncidentEdge(new_edge);

            new_edge->AddIncidentVertex(front);
            new_edge->AddIncidentVertex(pseudo_vertex);

            front->SetIncidentEdge(i, new_edge);

            shrinked_graph->AddEdge(new_edge);
          } else {
            shrinked_graph->AddEdge(incident_edge);
          }
        }
      }
    }
  }

  for (auto pair : pseudo_vertices) {
    pair.second->MergeDescendants(pair.first);
  }

  return shrinked_graph;
}

Graph* Graph::ShrinkBySwitches()
{
  Graph* shrinked_graph = new Graph(grid_);

  const string pseudo_vertex_prefix("PSV");
  int pseudo_vertex_counter = 0;

  ResetVerticesMarks();

  map<Vertex*, PseudoVertex*> pseudo_vertices;

  for (auto pair : vertices_) {
    Vertex* vertex = pair.second;

    if (!vertex->GetIsVisited()) {
      const string pseudo_vertex_name(pseudo_vertex_prefix + to_string(pseudo_vertex_counter++));

      Node* new_node = new Node(pseudo_vertex_name);

      grid_->GetSmartGrid()->AddEquipment(new_node);

      PseudoVertex* pseudo_vertex = new PseudoVertex(new_node);

      pseudo_vertex->MergeBySwitches(vertex);

      shrinked_graph->AddVertex(pseudo_vertex);

      vector<Vertex*> boundary_vertices(pseudo_vertex->GetBoundaryVertices());
      for (auto vertex : boundary_vertices) {
        pseudo_vertices.insert(make_pair(vertex, pseudo_vertex));
      }
    }
  }

  for (auto pair : edges_) {
    Edge* edge = pair.second;

    if (edge->GetType() == Edge::Type::SWITCH) {
      Vertex* vertex_a = edge->GetIncidentVertex(0);
      Vertex* vertex_b = edge->GetIncidentVertex(1);

      assert(pseudo_vertices.count(vertex_a) == 1 && pseudo_vertices.count(vertex_b) == 1);

      PseudoVertex* pseudo_vertex_a = pseudo_vertices.find(vertex_a)->second;
      PseudoVertex* pseudo_vertex_b = pseudo_vertices.find(vertex_b)->second;

      Edge* new_edge = new Edge(edge->GetRaw());

      pseudo_vertex_a->AddIncidentEdge(new_edge);
      pseudo_vertex_b->AddIncidentEdge(new_edge);

      new_edge->AddIncidentVertex(pseudo_vertex_a);
      new_edge->AddIncidentVertex(pseudo_vertex_b);

      shrinked_graph->AddEdge(new_edge);
    }
  }
  shrinked_graph->SetShrinkSource();

  return shrinked_graph;
}

void Graph::SetShrinkSource (){
  for (auto pair:vertices_) {
    PseudoVertex* pseudo = dynamic_cast<PseudoVertex*>(pair.second);
    assert(pseudo->GetGraph()->GetSourceNum() <= 1);
    if (pseudo->GetGraph()->GetSourceNum() == 1){
      source_vertices_.push_back(pair.second);
      pseudo->SetIsSource(true);

      Source* source_node = dynamic_cast<Source*>(pseudo->GetGraph()->GetSource(0)->GetRaw());
      remain_power_[source_node->GetName()]=source_node->GetOutputPower() - pseudo->GetConsumingPower();
      //cout << source_node->GetName() <<":" <<source_node->GetOutputPower() <<endl;
      pseudo->SetAssignSource(source_node->GetName());

    }
  }
  assert(source_vertices_.size() == 3);
}

int Graph::GetSourceNum(){
  return source_vertices_.size();
}
Vertex* Graph::GetSource(int index){
  return dynamic_cast<SourceVertex*>(source_vertices_[index]);
}

bool compare_function(Vertex* a, Vertex* b){
  return (a->GetDistanceDiff() > b->GetDistanceDiff());
}

void Graph::SetApplySource(){
  for (auto source:source_vertices_) {   //bfs for each source;
    ResetVerticesMarks();
    queue<Vertex*> bfs_queue;
    bfs_queue.push(source);
    source->SetSourceDistance(source, 0);
    source->SetIsVisted(true);
    while (!bfs_queue.empty()){
      Vertex* front = bfs_queue.front();
      bfs_queue.pop();
      for (int i=0; i<front->GetIncidentEdgesNum();++i){
        Vertex* child = front->GetIncidentEdge(i)->GetNeighbor(front);
        if (child->GetIsVisited()){
          continue;
        }
        child->SetIsVisted(true);
        child->SetSourceDistance(source,front->GetSourceDistance(source)+1);
        //cout << front->GetSourceDistance(source)+1 <<endl;
        bfs_queue.push(child);
      }
    }
  }

  vector<Vertex*> sort_vector;
  for (auto pair:vertices_){
    if (pair.second -> GetIsSource()){
      continue;
    }
    sort_vector.push_back(pair.second);
    pair.second -> CountDistanceDiff();
  }
  sort (sort_vector.begin(), sort_vector.end(), compare_function);  //ordering in decending order

  ////////////////////////////////////////////
  //  assigned without consider power constrain
  ////////////////////////////////////////////
  for (int i=0 ; i<sort_vector.size();++i) {
    PseudoVertex* target = dynamic_cast<PseudoVertex*>(sort_vector[i]);
    remain_power_[sort_vector[i]->GetSourcePriority(0)->GetAssignSource()]-=target->GetConsumingPower();
    target->SetAssignSource(sort_vector[i]->GetSourcePriority(0)->GetAssignSource());

    /*for (int j=0;j<sort_vector[i]->GetPriorityNum();++j ){
      if (remain_power_[sort_vector[i]->GetSourcePriority(j)->GetAssignSource()] > target->GetConsumingPower()){
      remain_power_[sort_vector[i]->GetSourcePriority(j)->GetAssignSource()]-=target->GetConsumingPower();
      target->SetAssignSource(sort_vector[i]->GetSourcePriority(j)->GetAssignSource());
      break;
      }
      }*/

  }


  ////////////////////////////////////////////
  //  adjusting
  ////////////////////////////////////////////
  for (auto pair:remain_power_){
    if (pair.second > 0)
      continue;
    queue<Vertex*> boundary_vertex;
    for (auto edge:edges_){
      PseudoVertex* a =dynamic_cast<PseudoVertex*>(edge.second->GetIncidentVertex(0));
      PseudoVertex* b =dynamic_cast<PseudoVertex*>(edge.second->GetIncidentVertex(1));
      if (a->GetAssignSource()!=pair.first){
        PseudoVertex* temp = a;
        a = b;
        b = temp;
      }
      if (a->GetAssignSource()==pair.first && b->GetAssignSource()!=pair.first) {
        boundary_vertex.push(a);
      }
    }
    while (pair.second < 0){
      PseudoVertex* target = dynamic_cast<PseudoVertex*>(boundary_vertex.front());
      boundary_vertex.pop();
      for (int i=0; i < target->GetIncidentEdgesNum();++i) {
        Vertex* neighbor = target->GetIncidentEdge(i)->GetNeighbor(target);
        if (target->GetAssignSource() == neighbor->GetAssignSource())
          continue;
        else {
          if (remain_power_[neighbor->GetAssignSource()] > target->GetConsumingPower()){
            remain_power_[neighbor->GetAssignSource()]-=target->GetConsumingPower();
            remain_power_[target->GetAssignSource()]+=target->GetConsumingPower();
            pair.second+=target->GetConsumingPower();
            target->SetAssignSource(neighbor->GetAssignSource());
            for (int j=0;j < target->GetIncidentEdgesNum();++j){
              Vertex* origin_neighbor = target->GetIncidentEdge(j)->GetNeighbor(target);
              if (origin_neighbor->GetAssignSource() == pair.first){
                boundary_vertex.push(origin_neighbor);
              }
            }
            break;
          }
        }
      }

    }
  }

  for (auto pair: vertices_) {
    if (pair.second->GetAssignSource()=="15xx(GREENS_PRAIRIE)") {
      pair.second->SetVoltage(79674.3);
    }else if (pair.second->GetAssignSource()=="06xx(SOUTH)"){
      pair.second->SetVoltage(79674.3);
    }else if (pair.second->GetAssignSource()=="07xx(MILLICAN)"){
      pair.second->SetVoltage(39837.2);
    }
    PseudoVertex* pseudo = dynamic_cast<PseudoVertex*>(pair.second);
    pseudo->GetGraph()->DeepSetApplySource(pseudo->GetAssignSource());
  }
}


void Graph::DeepSetApplySource(string set_source){
  for (auto pair:vertices_){

    pair.second->SetAssignSource(set_source);
    if (pair.second->GetType() == Vertex::Type::PSEUDO){
      PseudoVertex* pseudo = dynamic_cast<PseudoVertex*>(pair.second);
      pseudo->GetGraph()->DeepSetApplySource(set_source);
    }

    if (pair.second->GetAssignSource()=="15xx(GREENS_PRAIRIE)") {
      pair.second->SetVoltage(79674.3);
    }else if (pair.second->GetAssignSource()=="06xx(SOUTH)"){
      pair.second->SetVoltage(79674.3);
    }else if (pair.second->GetAssignSource()=="07xx(MILLICAN)"){
      pair.second->SetVoltage(39837.2);
    }else
      cout <<"something not asigned source!"<< pair.second->GetAssignSource() <<"!"<<endl;
  }
}

void Graph::Check() {
  ResetVerticesMarks();
  queue<Vertex*> bfs_queue;
  Vertex* root=source_vertices_[0];
  bfs_queue.push(root);
  root->SetIsVisted(true);
  while (!bfs_queue.empty()){
    Vertex* front = bfs_queue.front();
    bfs_queue.pop();
    for (int i=0; i<front->GetIncidentEdgesNum();++i){
      Vertex* child = front->GetIncidentEdge(i)->GetNeighbor(front);
      if (child->GetType()==Vertex::Type::PSEUDO){
        child = dynamic_cast<PseudoVertex*>(child)->GetBoundaryVertex(front->GetIncidentEdge(i));
      }
      if (!child->GetIsVisited()){
        child->SetIsVisted(true);
        bfs_queue.push(child);
      }
    }
  }

  for (auto pair:vertices_) {
    if (!pair.second->GetIsVisited())
      cout <<"no connect!"<<endl;
  }

}

void Graph::CountCost (){
  ResetVerticesMarks();

  for (auto source:source_vertices_) {   //bfs for each source;
    ResetVerticesMarks();
    queue<Vertex*> bfs_queue;
    bfs_queue.push(source);
    source->SetIsVisted(true);
    string source_name = source ->GetRaw()->GetName();
    vector <Vertex*> vector_leafs;
    //cout <<"Start:"<<source_name<<endl;
    while (!bfs_queue.empty()){
      Vertex* front = bfs_queue.front();
      bfs_queue.pop();
      for (int i=0; i<front->GetIncidentEdgesNum();++i){
        Vertex* child = front->GetIncidentEdge(i)->GetNeighbor(front);
        Edge* connect_edge = front->GetIncidentEdge(i);
        if (child->GetType()==Vertex::Type::PSEUDO){
          child = dynamic_cast<PseudoVertex*>(child)->GetBoundaryVertex(front->GetIncidentEdge(i));
          connect_edge = edges_[front->GetIncidentEdge(i)->GetRaw()->GetName()];
        }

        if (child->GetIsVisited() || child->GetAssignSource()!=source_name){
          continue;
        }
        child->SetIsVisted(true);
        child->SetParent(front);
        front->AddChild(child);
        bfs_queue.push(child);
        child->SetParentEdge(connect_edge);
      }
      if (front->GetChildrenNum() == 0){
        vector_leafs.push_back(front);
      } else if (front->GetType() == Vertex::Type::RESIDENT ){
        cout <<"error!!! :resident has more one edge"<<endl;
      }
    }
    /*
       for (auto pair: vertices_) {
       if (!pair.second->GetIsVisited() && pair.second->GetAssignSource()==source_name){
       cout <<"someting wrong!!"<<endl;
       }
       }
       */
    cout <<"process:"<<source_name<<" leafnum:"<<vector_leafs.size()<<endl;
    for (auto child : vector_leafs){
      //Vertex* child = pair.second;
      if (child->GetType() == Vertex::Type::RESIDENT && child->GetAssignSource() == source_name) {
        //cout <<"IN!! "<<endl;
        double load_current = dynamic_cast<ResidentVertex*>(child)->GetConsumingPower()/child->GetVoltage();
        //cout <<"load:"<< load_current<<endl;
        while (child!=source) {
          Vertex* parent = child->GetParent();
          Edge* connect_edge = child->GetParentEdge();
          assert(connect_edge->GetNeighbor(child)==parent);
          connect_edge->SetCurrent(connect_edge->GetCurrent()+load_current);
          child = parent;
        }
      }
    }
    //cout <<"finish:"<<source_name<<endl;
  }

  //cout <<"counting..."<<endl;
  wire_upgrade = 0.0;
  switch_change =0;

  for (auto pair:edges_) {
    if (pair.second->GetType()==Edge::Type::EDGE){
      Wire* wire = pair.second->GetRaw();
      if (pair.second->GetCurrent() > wire->GetCurrentLimit()){
        //cout <<"Current:"<< pair.second->GetCurrent()<< "  Limit:"<< wire->GetCurrentLimit()<<endl;
        wire_upgrade += pair.second->GetCurrent()-wire->GetCurrentLimit();
      }
    }else if(pair.second->GetType()==Edge::Type::SWITCH){
      Switch* switches = dynamic_cast<Switch*> (pair.second->GetRaw());
      Vertex* a = pair.second->GetIncidentVertex(0);
      Vertex* b = pair.second->GetIncidentVertex(1);

      if ( (a->GetAssignSource() != b->GetAssignSource() && switches->GetIsOn()) || (a->GetAssignSource() == b->GetAssignSource() && !switches->GetIsOn() ))
        switch_change++;
    }
  }
  cout << "wire upgrade :" << wire_upgrade << endl;
  cout << "wire change  :" << switch_change << endl;
}

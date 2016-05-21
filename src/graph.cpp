#include "graph.hpp"
#include "pseudo_vertex.hpp"

#include <cassert>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

Graph::Graph(Grid* grid) : grid_(grid), root_(nullptr)
{
}

Graph::~Graph()
{
  /* for (auto pair : vertices_) { */
  /*   if (pair.second != nullptr) { */
  /*     delete pair.second; */
  /*     pair.second = nullptr; */
  /*   } */
  /* } */
  /* for (auto pair : edges_) { */
  /*   if (pair.second != nullptr) { */
  /*     delete pair.second; */
  /*     pair.second = nullptr; */
  /*   } */
  /* } */
}

void Graph::Print() const
{
  cout << "Graph: "<< endl;
  for (auto pair : vertices_) {
    pair.second->Print();
    cout << endl;
  }
  for (auto pair : edges_) {
    pair.second->Print();
    cout << endl;
  }
}

Graph* Graph::Shrink()
{
  root_ = source_vertices_[0];

  MarkArticulationPoints();

  // Clean all articulation points on the paths between every pair of source
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

  // Clean all the articulation points connecting a resident directly to avoid
  // making useless pseudo vertices each containing just a single resident.
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

  Graph* shrinked_graph = ShrinkByArticulationPoints();

  shrinked_graph = shrinked_graph->ShrinkBySwitches();

  shrinked_graph->Print();

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

            Node* node = new Node(pseudo_vertex_name);

            grid_->GetSmartGrid()->AddEquipment(node);

            PseudoVertex* pseudo_vertex = new PseudoVertex(new Node(pseudo_vertex_name));

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

      Node* node = new Node(pseudo_vertex_name);

      grid_->GetSmartGrid()->AddEquipment(node);

      PseudoVertex* pseudo_vertex = new PseudoVertex(node);

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

  return shrinked_graph;
}

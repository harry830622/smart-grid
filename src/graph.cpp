#include "graph.hpp"
#include "pseudo_vertex.hpp"

#include <cassert>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

Graph::Graph()
{
}

Graph::~Graph()
{
  for (auto pair : vertices_) {
    if (pair.second != nullptr) {
      delete pair.second;
      pair.second = nullptr;
    }
  }
  for (auto pair : edges_) {
    if (pair.second != nullptr) {
      delete pair.second;
      pair.second = nullptr;
    }
  }
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
  DFS();
  MarkArticulationPoints();

  Vertex* root = source_vertices_[2];

  for (auto source_vertex : source_vertices_) {
    if (source_vertex != root) {
      Vertex* vertex = source_vertex;
      while (vertex != root) {
        vertex->SetIsArticulate(false);
        vertex = vertex->GetParent();
      }
    }
  }

  for (auto pair : vertices_) {
    pair.second->ResetMarks();
  }

  Graph* shrinked_graph = new Graph;

  queue<Vertex*> bfs_queue;

  const string pseudo_vertex_prefix("PV");
  int pseudo_vertex_counter = 0;

  root->SetDepth(0);

  shrinked_graph->AddVertex(root);

  map<Vertex*, PseudoVertex*> pseudo_vertices; // Index by the vertex

  bfs_queue.push(root);
  while (!bfs_queue.empty()) {
    Vertex* vertex = bfs_queue.front();
    bfs_queue.pop();

    int depth = vertex->GetDepth() + 1;
    for (int i = 0; i < vertex->GetIncidentEdgesNum(); ++i) {
      Edge* incident_edge = vertex->GetIncidentEdge(i);
      Vertex* child = incident_edge->GetTheOtherVertex(vertex);

      if (child != vertex->GetParent()) {
        bool is_child_child_a_resident = false;
        for (int j = 0; j < child->GetIncidentEdgesNum(); ++j) {
          Vertex* child_child = child->GetIncidentEdge(j)->GetTheOtherVertex(child);

          if (child_child == child->GetParent()) {
            continue;
          }

          if (child_child->GetType() == Vertex::Type::RESIDENT) {
            is_child_child_a_resident = true;
            break;
          }
        }

        if (!child->GetIsVisited() && (!child->GetIsArticulate() || is_child_child_a_resident)) {
          child->SetDepth(depth);
          child->SetParent(vertex);

          bfs_queue.push(child);

          shrinked_graph->AddVertex(child);
          shrinked_graph->AddEdge(incident_edge);
        } else if (child->GetIsVisited() && !child->GetIsArticulate()) {
          shrinked_graph->AddEdge(incident_edge);
        } else if (!child->GetIsVisited() && child->GetIsArticulate()) {
          child->SetDepth(depth);
          child->SetParent(vertex);

          if (child->GetDepth() < 4) {
            bfs_queue.push(child);

            shrinked_graph->AddVertex(child);
            shrinked_graph->AddEdge(incident_edge);
          } else {
            const string pseudo_vertex_name(pseudo_vertex_prefix + to_string(pseudo_vertex_counter++));
            PseudoVertex* pseudo_vertex = new PseudoVertex(new Node(pseudo_vertex_name)); // TODO: Avoid memory leak

            pseudo_vertex->AddBoundaryVertex(incident_edge, child);

            Edge* edge = new Edge(incident_edge->GetRaw());

            pseudo_vertex->AddIncidentEdge(edge);

            edge->AddIncidentVertex(vertex);
            edge->AddIncidentVertex(pseudo_vertex);

            shrinked_graph->AddVertex(pseudo_vertex);
            shrinked_graph->AddEdge(edge);

            pseudo_vertices.insert(make_pair(child, pseudo_vertex));
          }
        } else {
          assert(pseudo_vertices.count(child) == 1);

          PseudoVertex* pseudo_vertex = pseudo_vertices.find(child)->second;

          pseudo_vertex->AddBoundaryVertex(incident_edge, child);

          Edge* edge = new Edge(incident_edge->GetRaw());

          edge->AddIncidentVertex(vertex);
          edge->AddIncidentVertex(pseudo_vertex);

          shrinked_graph->AddEdge(edge);
        }
      }
    }
  }

  /* for (auto pair : pseudo_vertices) { */
  /*   pair.first->Print(); */
  /*   pair.second->Print(); */
  /*   cout << endl; */
  /* } */

  // TODO: Shrink

  /* shrinked_graph->Print(); */

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

void Graph::AddVertex(Vertex* vertex)
{
  vertices_.insert(make_pair(vertex->GetRaw()->GetName(), vertex));

  if (vertex->GetType() == Vertex::Type::SOURCE) {
    source_vertices_.push_back(dynamic_cast<SourceVertex*>(vertex));
  }
}

void Graph::AddEdge(Edge* edge)
{
  edges_.insert(make_pair(edge->GetRaw()->GetName(), edge));
}

void DFSVisit(Vertex* vertex, int depth)
{
  vertex->SetDepth(depth);
  vertex->SetLow(depth);
  for (int i = 0; i < vertex->GetIncidentEdgesNum(); ++i) {
    Vertex* child = vertex->GetIncidentEdge(i)->GetTheOtherVertex(vertex);
    if (!child->GetIsVisited()) {
      child->SetParent(vertex);
      vertex->IncrementChildrenNum();
      DFSVisit(child, depth + 1);
    }
  }
}

void Graph::DFS()
{
  for (auto pair : vertices_) {
    if (!pair.second->GetIsVisited()) {
      DFSVisit(pair.second, 0);
    }
  }
}

void Graph::MarkArticulationPoints()
{
  vector<Vertex*> vertices;
  for (auto pair : vertices_) {
    vertices.push_back(pair.second);
  }

  sort(vertices.begin(), vertices.end(), [](Vertex* v1, Vertex* v2) {return v1->GetDepth() > v2->GetDepth();});

  for (auto vertex : vertices) {
    for (int i = 0; i < vertex->GetIncidentEdgesNum(); ++i) {
      Vertex* child = vertex->GetIncidentEdge(i)->GetTheOtherVertex(vertex);

      if (child != vertex->GetParent() && child->GetLow() < vertex->GetLow()) {
        vertex->SetLow(child->GetLow());
      }
    }
  }

  for (auto vertex : vertices) {
    if (vertex->GetIsDFSRoot()) {
      continue;
    }

    Vertex* parent = vertex->GetParent();

    if (parent->GetIsArticulate()) {
      continue;
    }

    if (parent->GetIsDFSRoot()) {
      if (parent->GetChildrenNum() > 1) {
        parent->SetIsArticulate(true);
      }
      continue;
    }

    if (vertex->GetLow() >= parent->GetDepth()) {
      parent->SetIsArticulate(true);
    }
  }
}

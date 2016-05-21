#include "pseudo_vertex.hpp"

#include <cassert>
#include <iostream>
#include <queue>

using namespace std;

PseudoVertex::PseudoVertex(Node* raw)
  : Vertex(raw, Vertex::Type::PSEUDO), consuming_power_(0.0), graph_(nullptr)
{
}

PseudoVertex::~PseudoVertex()
{
  delete graph_;
  graph_ = nullptr;
}

void PseudoVertex::Print() const
{
  cout << "Pseudo Vertex: " << endl;
  cout << "  consuming_power_: " << consuming_power_ << endl;
  Vertex::Print();
}

void PseudoVertex::MergeDescendants(Vertex* root)
{
  assert(graph_ == nullptr);
  assert(root != nullptr);

  graph_ = new Graph(root->GetGrid());

  graph_->SetRoot(root);

  queue<Vertex*> bfs_queue;
  root->SetIsVisted();
  bfs_queue.push(root);
  while (!bfs_queue.empty()) {
    Vertex* front = bfs_queue.front();
    bfs_queue.pop();

    graph_->AddVertex(front);

    for (int i = 0; i < front->GetIncidentEdgesNum(); ++i) {
      Edge* incident_edge = front->GetIncidentEdge(i);
      Vertex* child = incident_edge->GetNeighbor(front);

      if (child != front->GetParent()) {
        if (!child->GetIsVisited()) {
          child->SetIsVisted();

          bfs_queue.push(child);

          front->AddChild(child);
          child->SetParent(front);

          if (child->GetType() == Vertex::Type::RESIDENT) {
            ResidentVertex* resident_vertex = dynamic_cast<ResidentVertex*>(child);

            consuming_power_ += resident_vertex->GetConsumingPower();
          }
        }
        graph_->AddEdge(incident_edge);
      }
    }
  }
}

void PseudoVertex::MergeBySwitches(Vertex* root)
{
  assert(graph_ == nullptr);
  assert(root != nullptr);

  graph_ = new Graph(root->GetGrid());

  graph_->SetRoot(root);

  queue<Vertex*> bfs_queue;
  root->SetIsVisted();
  bfs_queue.push(root);
  while (!bfs_queue.empty()) {
    Vertex* front = bfs_queue.front();
    bfs_queue.pop();

    graph_->AddVertex(front);

    for (int i = 0; i < front->GetIncidentEdgesNum(); ++i) {
      Edge* incident_edge = front->GetIncidentEdge(i);
      Vertex* child = incident_edge->GetNeighbor(front);

      if (incident_edge->GetType() == Edge::Type::SWITCH) {
        AddBoundaryVertex(incident_edge, front);
        continue;
      }

      if (child != front->GetParent()) {
        if (!child->GetIsVisited()) {
          child->SetIsVisted();

          bfs_queue.push(child);

          front->AddChild(child);
          child->SetParent(front);

          if (child->GetType() == Vertex::Type::RESIDENT) {
            ResidentVertex* resident_vertex = dynamic_cast<ResidentVertex*>(child);

            consuming_power_ += resident_vertex->GetConsumingPower();
          } else if (child->GetType() == Vertex::Type::PSEUDO) {
            PseudoVertex* resident_vertex = dynamic_cast<PseudoVertex*>(child);

            consuming_power_ += resident_vertex->GetConsumingPower();
          }
        }
        graph_->AddEdge(incident_edge);
      }
    }
  }
}

double PseudoVertex::GetConsumingPower() const
{
  return consuming_power_;
}

Graph* PseudoVertex::GetGraph() const
{
  return graph_;
}

Vertex* PseudoVertex::GetBoundaryVertex(Edge* edge) const
{
  if (boundary_vertices_.count(edge) == 0) {
    return nullptr;
  }

  return boundary_vertices_.find(edge)->second;
}

vector<Vertex*> PseudoVertex::GetBoundaryVertices() const
{
  vector<Vertex*> boundary_vertices;

  for (auto pair : boundary_vertices_) {
    boundary_vertices.push_back(pair.second);
  }

  return boundary_vertices;
}

void PseudoVertex::AddBoundaryVertex(Edge* edge, Vertex* vertex)
{
  boundary_vertices_.insert(make_pair(edge, vertex));
}

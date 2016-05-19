#include "pseudo_vertex.hpp"

#include <cassert>
#include <iostream>
#include <queue>

using namespace std;

PseudoVertex::PseudoVertex(Node* raw)
  : Vertex(raw, Vertex::Type::PSEUDO), consuming_power_(0.0), graph_(nullptr), root_(nullptr)
{
}

void PseudoVertex::Print() const
{
  cout << "Pseudo Vertex: " << endl;
  cout << "  consuming_power_: " << consuming_power_ << endl;
  Vertex::Print();
}

void PseudoVertex::MergeDescendants(Vertex* root)
{
  assert(root_ == nullptr);
  assert(root != nullptr);

  root_ = root;

  graph_ = new Graph(root_->GetGrid());

  queue<Vertex*> bfs_queue;
  root_->SetIsVisted();
  bfs_queue.push(root_);
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

          graph_->AddVertex(child);
        } else {
          graph_->AddEdge(incident_edge);
        }
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

void PseudoVertex::AddBoundaryVertex(Edge* edge, Vertex* vertex)
{
  boundary_vertices_.insert(make_pair(edge, vertex));
}

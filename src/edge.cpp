#include "edge.hpp"

#include <cassert>
#include <iostream>

using namespace std;

Edge::Edge(Wire* raw, Type type) : raw_(raw), type_(type), current_(0.0)
{
}

void Edge::Print() const
{
  cout << "Edge: " << endl;
  cout << "  incident_vertices_: ";
  for (auto vertex : incident_vertices_) {
    cout << vertex->GetRaw()->GetName() << " ";
  }
  cout << endl;
  raw_->Print();
}

Grid* Edge::GetGrid() const
{
  return grid_;
}

Wire* Edge::GetRaw() const
{
  return raw_;
}

Edge::Type Edge::GetType() const
{
  return type_;
}

double Edge::GetCurrent() const
{
  return current_;
}

Vertex* Edge::GetIncidentVertex(int i) const
{
  assert(i < 2);

  return incident_vertices_[i];
}

Vertex* Edge::GetNeighbor(Vertex* vertex) const
{
  if (incident_vertices_[0] != vertex) {
    return incident_vertices_[0];
  } else {
    return incident_vertices_[1];
  }
}

void Edge::SetGrid(Grid* grid)
{
  grid_ = grid;
}

void Edge::AddIncidentVertex(Vertex* vertex)
{
  assert(incident_vertices_.size() < 2);
  incident_vertices_.push_back(vertex);
}

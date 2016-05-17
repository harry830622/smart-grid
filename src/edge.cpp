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
  raw_->Print();
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

Vertex* Edge::GetTheOtherVertex(Vertex* vertex) const
{
  if (incident_vertices_[0] != vertex) {
    return incident_vertices_[0];
  } else {
    return incident_vertices_[1];
  }
}

void Edge::AddIncidentVertex(Vertex* vertex)
{
  assert(incident_vertices_.size() < 2);
  incident_vertices_.push_back(vertex);
}

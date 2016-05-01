#include "edge.hpp"

#include <cassert>

Edge::Edge(Wire* raw) : raw_(raw)
{
}

Wire* Edge::GetRaw() const
{
  return raw_;
}

void Edge::AddIncidentVertex(Vertex* vertex)
{
  assert(incident_vertices_.size() < 2);
  incident_vertices_.push_back(vertex);
}

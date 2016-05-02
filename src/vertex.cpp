#include "vertex.hpp"

Vertex::Vertex(Node* raw) : raw_(raw), voltage_(0.0)
{
}

Node* Vertex::GetRaw() const
{
  return raw_;
}

void Vertex::AddIncidentEdge(Edge* edge)
{
  incident_edges_.push_back(edge);
}

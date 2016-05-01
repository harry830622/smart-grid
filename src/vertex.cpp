#include "vertex.hpp"

Vertex::Vertex(Node* raw) : raw_(raw)
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

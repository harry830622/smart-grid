#include "edge.hpp"

#include <cassert>

Edge::Edge(Node* raw)
  :raw_(raw)
{
}

Edge::~Edge()
{
  delete raw_;
}

Node* Edge::GetRaw()
{
  return raw_;
}

void Edge::AddVertex(Vertex* vertex)
{
  assert(vertices_.size() < 2);
  vertices_.push_back(vertex);
}

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

void Edge::AddVertex(Vertex* vertex)
{
  vertices_.push_back(vertex);
  assert(vertices_.size() <= 2);
}

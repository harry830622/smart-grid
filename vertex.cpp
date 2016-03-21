#include "vertex.hpp"

Vertex::Vertex(Node* raw)
  :raw_(raw)
{
}

Vertex::~Vertex()
{
  delete raw_;
}

void Vertex::Print()
{
  raw_->Print();
}

Node* Vertex::GetRaw()
{
  return raw_;
}

void Vertex::AddEdge(Edge* edge)
{
  edges_.push_back(edge);
}

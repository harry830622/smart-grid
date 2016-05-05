#include "vertex.hpp"

#include <iostream>

using namespace std;

Vertex::Vertex(Node* raw, Type type) : raw_(raw), type_(type), voltage_(0.0)
{
}

void Vertex::Print() const
{
  cout << "Vertex: " << endl;
  raw_->Print();
}

Node* Vertex::GetRaw() const
{
  return raw_;
}

Vertex::Type Vertex::GetType() const
{
  return type_;
}

void Vertex::AddIncidentEdge(Edge* edge)
{
  incident_edges_.push_back(edge);
}

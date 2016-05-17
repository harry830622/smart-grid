#include "pseudo_vertex.hpp"

#include <iostream>

using namespace std;

PseudoVertex::PseudoVertex(Node* raw) : Vertex(raw, Vertex::Type::PSEUDO), consuming_power_(0.0)
{
}

void PseudoVertex::Print() const
{
  cout << "Pseudo Vertex: " << endl;
  cout << "  consuming_power_: " << consuming_power_ << endl;
  Vertex::Print();
}

double PseudoVertex::GetConsumingPower() const
{
  return consuming_power_;
}

void PseudoVertex::AddBoundaryVertex(Edge* edge, Vertex* vertex)
{
  boundary_vertices_.insert(make_pair(edge, vertex));
}

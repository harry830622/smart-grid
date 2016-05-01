#include "edge.hpp"

#include <cassert>
#include <iostream>

using namespace std;

Edge::Edge(Node raw)
  :raw_(raw)
{
}

void Edge::Print()
{
  cout << "Edge" << endl;
  cout << " x1: " << vertices_[0]->GetCoordinate().GetX() << " y1: " << vertices_[0]->GetCoordinate().GetY() << " z1: " << vertices_[0]->GetCoordinate().GetZ() << endl;
  cout << " x2: " << vertices_[1]->GetCoordinate().GetX() << " y2: " << vertices_[1]->GetCoordinate().GetY() << " z2: " << vertices_[1]->GetCoordinate().GetZ() << endl;
  raw_.Print();
}

Node Edge::GetRaw()
{
  return raw_;
}

void Edge::AddVertex(Vertex* vertex)
{
  assert(vertices_.size() < 2);
  vertices_.push_back(vertex);
}

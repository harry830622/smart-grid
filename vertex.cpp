#include "vertex.hpp"

#include <iostream>

using namespace std;

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
  cout << "Vertex" << endl;
  cout << "  x: " << coordinate_.GetX() << " y: " << coordinate_.GetY() << " z: " << coordinate_.GetZ() << endl;
  raw_->Print();
}

Node* Vertex::GetRaw()
{
  return raw_;
}

Point Vertex::GetCoordinate()
{
  return coordinate_;
}

void Vertex::SetCoordinateX(double x)
{
  coordinate_.SetX(x);
}

void Vertex::SetCoordinateY(double y)
{
  coordinate_.SetY(y);
}

void Vertex::SetCoordinateZ(double z)
{
  coordinate_.SetZ(z);
}

void Vertex::AddEdge(Edge* edge)
{
  edges_.push_back(edge);
}

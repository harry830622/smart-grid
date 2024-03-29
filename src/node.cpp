#include "node.hpp"

#include <iostream>

using namespace std;

Node::Node(string name, Type type) : Equipment(name, Equipment::Type::NODE), type_(type)
{
}

void Node::Print() const
{
  Equipment::Print();
  cout << "Node: " << endl;
  cout << "  x: " << coordinate_.GetX() << " y: " << coordinate_.GetY() << " z: " << coordinate_.GetZ() << endl;
}

Point Node::GetCoordinate() const
{
  return coordinate_;
}

Node::Type Node::GetType() const
{
  return type_;
}

void Node::SetCoordinateX(double x)
{
  coordinate_.SetX(x);
}

void Node::SetCoordinateY(double y)
{
  coordinate_.SetY(y);
}

void Node::SetCoordinateZ(double z)
{
  coordinate_.SetZ(z);
}

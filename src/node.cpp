#include "node.hpp"

#include <iostream>

using namespace std;

Node::Node(string name, Type type) : Equipment(name), type_(type)
{
}

/* Node::~Node() */
/* { */
/*   cout << "Destruct Node" << endl; */
/* } */


void Node::Print() const
{
  Equipment::Print();
  cout << "Node: " << endl;
  cout << "  x: " << coordinate_.GetX() << " y: " << coordinate_.GetY() << " z: " << coordinate_.GetZ() << endl;
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

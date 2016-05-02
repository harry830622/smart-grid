#include "node.hpp"

#include <iostream>

using namespace std;

Node::Node(string name, Type type) : Equipment(name), type_(type)
{
}

void Node::Print() const
{
  Equipment::Print();
  cout << "Node: " << endl;
  cout << "  x: " << coordinate_.GetX() << " y: " << coordinate_.GetY() << " z: " << coordinate_.GetZ() << endl;
}

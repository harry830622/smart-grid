#include "node.hpp"

#include <iostream>

using namespace std;

Node::Node(std::string name, Type type)
  :type_(type), name_(name), phase_(name.back())
{
}

Node::~Node()
{
}

void Node::Print()
{
  string type;
  switch (static_cast<int>(type_)) {
    case 0:
      type = "NODE";
      break;
    case 1:
      type = "SOURCE";
      break;
    case 2:
      type = "RESIDENT";
      break;
    case 3:
      type = "WIRE";
      break;
    case 4:
      type = "SWITCH";
      break;
  }
  cout << "Node: " << type << endl;
  cout << "  name: " << name_ << endl;
  cout << "  phase: " << phase_ << endl;
}

Node::Type Node::GetType()
{
  return type_;
}

string Node::GetName()
{
  return name_;
}

char Node::GetPhase()
{
  return phase_;
}

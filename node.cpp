#include "node.hpp"

#include <iostream>

using namespace std;

Node::Node(std::string name, Type type)
  :name_(name), type_(type)
{
}

Node::~Node()
{
}

void Node::Print() const
{
  string type;
  switch (type_) {
    case Type::NODE:
      type = "NODE";
      break;
    case Type::SOURCE:
      type = "SOURCE";
      break;
    case Type::RESIDENT:
      type = "RESIDENT";
      break;
    case Type::WIRE:
      type = "WIRE";
      break;
    case Type::SWITCH:
      type = "SWITCH";
      break;
  }
  cout << "Node: " << type << endl;
  cout << "  name: " << name_ << endl;
}

Node::Type Node::GetType() const
{
  return type_;
}

string Node::GetName() const
{
  return name_;
}

#include "node.hpp"

#include <iostream>

using namespace std;

Node::Node(std::string name)
  :name_(name), phase_(name.back())
{
}

Node::~Node()
{
}

void Node::Print()
{
  cout << "Node: " << endl;
  cout << "  name: " << name_ << endl;
  cout << "  phase: " << phase_ << endl;
}

char Node::GetPhase()
{
  return phase_;
}

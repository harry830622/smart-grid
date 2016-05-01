#include "switch.hpp"

#include <iostream>
#include <string>

using namespace std;

Switch::Switch(string name, bool is_on)
  :Node(name, Node::Type::SWITCH), is_on_(is_on)
{
}

void Switch::Print() const
{
  Node::Print();
  cout << "  is on? " << is_on_ << endl;
}

bool Switch::GetIsOn() const
{
  return is_on_;
}

void Switch::SetIsOn(bool is_on)
{
  is_on_ = is_on;
}

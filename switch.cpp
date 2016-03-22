#include "switch.hpp"

#include <string>

using namespace std;

Switch::Switch(string name, bool is_on)
  :Node(name, Node::Type::SWITCH), is_on_(is_on)
{
}

bool Switch::GetIsOn()
{
  return is_on_;
}

void Switch::SetIsOn(bool is_on)
{
  is_on_ = is_on;
}

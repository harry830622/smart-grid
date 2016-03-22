#include "wire.hpp"

Wire::Wire(std::string name, double resistence, double current_limit)
  :Node(name, Node::Type::WIRE), resistence_(resistence), current_limit_(current_limit)
{
}

double Wire::GetResistence()
{
  return resistence_;
}

double Wire::GetCurrentLimit()
{
  return current_limit_;
}

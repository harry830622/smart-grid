#include "wire.hpp"

#include <iostream>

using namespace std;

Wire::Wire(std::string name, double resistence, double current_limit)
  :Node(name, Node::Type::WIRE), resistence_(resistence), current_limit_(current_limit)
{
}

void Wire::Print() const
{
  Node::Print();
  cout << "  resistence: " << resistence_ << endl;
  cout << "  current_limit: " << current_limit_ << endl;
}

double Wire::GetResistence() const
{
  return resistence_;
}

double Wire::GetCurrentLimit() const
{
  return current_limit_;
}

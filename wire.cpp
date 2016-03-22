#include "wire.hpp"

#include <iostream>

using namespace std;

Wire::Wire(std::string name, double resistence, double current_limit)
  :Node(name, Node::Type::WIRE), resistence_(resistence), current_limit_(current_limit)
{
}

void Wire::Print()
{
  Node::Print();
  cout << "  resistence: " << resistence_ << endl;
  cout << "  current_limit: " << current_limit_ << endl;
}

double Wire::GetResistence()
{
  return resistence_;
}

double Wire::GetCurrentLimit()
{
  return current_limit_;
}

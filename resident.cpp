#include "resident.hpp"

Resident::Resident(std::string name, double power)
  :Node(name), power_(power), source_(0)
{
}

void Resident::Print()
{
  Node::Print();
}

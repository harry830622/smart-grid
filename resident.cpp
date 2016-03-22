#include "resident.hpp"

#include <iostream>

using namespace std;

Resident::Resident(std::string name, double power)
  :Node(name, Node::Type::RESIDENT), power_(power), source_(nullptr)
{
}

void Resident::Print()
{
  Node::Print();
  cout << "  power: " << power_ << endl;
}

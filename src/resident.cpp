#include "resident.hpp"

#include <iostream>

using namespace std;

Resident::Resident(std::string name, double consuming_power)
  : Node(name, Node::Type::RESIDENT), consuming_power_(consuming_power)
{
}

void Resident::Print() const
{
  Node::Print();
  cout << "Resident: " << endl;
  cout << "  consuming_power: " << consuming_power_ << endl;
}

double Resident::GetConsumingPower() const
{
  return consuming_power_;
}

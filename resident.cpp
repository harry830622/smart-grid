#include "resident.hpp"

#include <iostream>

using namespace std;

Resident::Resident(std::string name, double power)
  :Node(name, Node::Type::RESIDENT), power_(power), source_(nullptr)
{
}

void Resident::Print() const
{
  Node::Print();
  cout << "  power: " << power_ << endl;
  cout << "  source: " << source_->GetName() << endl;
}

double Resident::GetPower() const
{
  return power_;
}

void Resident::SetSource(Source* source)
{
  source_ = source;
}

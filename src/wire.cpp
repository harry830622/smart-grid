#include "wire.hpp"

#include <iostream>

using namespace std;

Wire::Wire(string name, double resistance, double current_limit, Type type)
  : Equipment(name, Equipment::Type::WIRE), type_(type), resistance_(resistance), current_limit_(current_limit)
{
}

void Wire::Print() const
{
  Equipment::Print();
  cout << "Wire: " << endl;
  cout << "  resistance: " << resistance_ << " current_limit: " << current_limit_ << endl;
}

Wire::Type Wire::GetType() const
{
  return type_;
}

double Wire::GetResistance() const
{
  return resistance_;
}

double Wire::GetCurrentLimit() const
{
  return current_limit_;
}

void Wire::SetCurrentLimit(double current_limit)
{
  current_limit_ = current_limit;
}

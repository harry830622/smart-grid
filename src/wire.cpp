#include "wire.hpp"

using namespace std;

Wire::Wire(string name, Type type, double resistance, double current_limit)
  : Equipment(name), type_(type), resistance_(resistance), current_limit_(current_limit)
{
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

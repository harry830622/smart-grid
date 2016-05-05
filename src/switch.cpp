#include "switch.hpp"

#include <limits>
#include <iostream>

using namespace std;

Switch::Switch(string name, bool is_on)
  : Wire(name, Wire::Type::SWITCH), is_on_(is_on)
{
  SetIsOn(is_on_);
}

/* Switch::~Switch() */
/* { */
/*   cout << "Destruct Switch" << endl; */
/* } */


void Switch::Print() const
{
  Wire::Print();
  cout << "Switch: " << endl;
  cout << "  is_on: " << is_on_ << endl;
}

bool Switch::GetIsOn() const
{
  return is_on_;
}
void Switch::SetIsOn(bool is_on)
{
  is_on_ = is_on;
  if (is_on_) {
    SetCurrentLimit(numeric_limits<double>::max());
  } else {
    SetCurrentLimit(0.0);
  }
}

void Switch::TurnOn()
{
  SetIsOn();
}

void Switch::TurnOff()
{
  SetIsOn(false);
}

#include "equipment.hpp"

#include <iostream>

using namespace std;

Equipment::Equipment(string name) : name_(name)
{
}

void Equipment::Print() const
{
  cout << "Equipment: " << name_ << endl;
}

string Equipment::GetName() const
{
  return name_;
}

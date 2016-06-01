#include "equipment.hpp"

#include <iostream>

using namespace std;

Equipment::Equipment(string name, Type type) : type_(type), name_(name)
{
}

void Equipment::Print() const
{
  cout << "Equipment: " << name_ << endl;
}

Equipment::Type Equipment::GetType() const
{
  return type_;
}

string Equipment::GetName() const
{
  return name_;
}

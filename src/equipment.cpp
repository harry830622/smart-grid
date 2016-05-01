#include "equipment.hpp"

using namespace std;

Equipment::Equipment(string name) : name_(name)
{
}

string Equipment::GetName() const
{
  return name_;
}

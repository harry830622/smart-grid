#include "source.hpp"

#include <iostream>

using namespace std;

Source::Source(std::string name, double power)
  :Node(name, Node::Type::SOURCE), power_(power)
{
}

void Source::Print() const
{
  Node::Print();
  cout << "  power: " << power_ << endl;
  cout << "  loading residents:" << endl;
  for (auto pair : loading_residents_) {
    cout << "    " << pair.second->GetName() << endl;
  }
}

double Source::GetPower() const
{
  return power_;
}

double Source::LoadingPower() const
{
  double loading_power = 0;
  for (auto pair : loading_residents_) {
    loading_power += pair.second->GetPower();
  }

  return loading_power;
}

double Source::RemainingPower() const
{
  return power_ - LoadingPower();
}

void Source::AddLoadingResident(Resident* resident)
{
  loading_residents_.insert(make_pair(resident->GetName(), resident));
}

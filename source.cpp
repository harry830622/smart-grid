#include "source.hpp"

#include <iostream>

using namespace std;

Source::Source(std::string name, double power)
  :Node(name, Node::Type::SOURCE), power_(power)
{
}

void Source::Print()
{
  Node::Print();
  cout << "  power: " << power_ << endl;
  cout << "  loading residents:" << endl;
  for (auto resident : loading_residents_) {
    cout << "    " << resident->GetName() << endl;
  }
}

double Source::GetPower()
{
  return power_;
}

double Source::LoadingPower()
{
  double loading_power = 0;
  for (Resident* resident : loading_residents_) {
    loading_power += resident->GetPower();
  }

  return loading_power;
}

double Source::RemainingPower()
{
  return power_ - LoadingPower();
}

void Source::AddLoadingResident(Resident* resident)
{
  loading_residents_.push_back(resident);
}

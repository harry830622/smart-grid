#include "source.hpp"

using namespace std;

Source::Source(string name, double output_power)
  : Node(name, Node::Type::SOURCE), output_power_(output_power)
{
}

double Source::GetOutputPower() const
{
  return output_power_;
}

double Source::LoadingPower() const
{
  double loading_power = 0;
  for (auto pair : loading_residents_) {
    loading_power += pair.second->GetConsumingPower();
  }

  return loading_power;
}

double Source::RemainingPower() const
{
  return output_power_ - LoadingPower();
}

void Source::AddLoadingResident(Resident* resident)
{
  loading_residents_.insert(make_pair(resident->GetName(), resident));
}

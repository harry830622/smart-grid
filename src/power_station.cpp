#include "power_station.hpp"

PowerStation::PowerStation(Source* raw) : Vertex(raw)
{
  source_ = raw;
}

double PowerStation::OutputPower() const
{
  return source_->GetOutputPower();
}

double PowerStation::LoadingPower() const
{
  double loading_power = 0;
  for (auto pair : loading_residents_) {
    loading_power += pair.second->GetConsumingPower();
  }

  return loading_power;
}

double PowerStation::RemainingPower() const
{
  return OutputPower() - LoadingPower();
}

void PowerStation::AddLoadingResident(Resident* resident)
{
  loading_residents_.insert(make_pair(resident->GetName(), resident));
}

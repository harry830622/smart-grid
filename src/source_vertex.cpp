#include "source_vertex.hpp"

#include <iostream>

using namespace std;

SourceVertex::SourceVertex(Source* raw) : Vertex(raw, Vertex::Type::SOURCE), source_(raw)
{
}

void SourceVertex::Print() const
{
  cout << "Source Vertex: " << endl;
  Vertex::Print();
}

double SourceVertex::GetOutputPower() const
{
  return source_->GetOutputPower();
}

double SourceVertex::GetLoadingPower() const
{
  double loading_power = 0;
  for (auto pair : loading_residents_) {
    loading_power += pair.second->GetConsumingPower();
  }

  return loading_power;
}

double SourceVertex::GetRemainingPower() const
{
  return GetOutputPower() - GetLoadingPower();
}

void SourceVertex::AddLoadingResident(ResidentVertex* resident)
{
  loading_residents_.insert(make_pair(resident->GetName(), resident));
}

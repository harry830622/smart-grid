#include "resident.hpp"

using namespace std;

Resident::Resident(std::string name, double consuming_power)
  : Node(name, Node::Type::RESIDENT), consuming_power_(consuming_power)
{
}

double Resident::GetConsumingPower() const
{
  return consuming_power_;
}

void Resident::SetSource(Source* source)
{
  source_ = source;
}

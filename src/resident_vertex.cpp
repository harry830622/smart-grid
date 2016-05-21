#include "resident_vertex.hpp"

#include <iostream>

using namespace std;

ResidentVertex::ResidentVertex(Resident* raw) : Vertex(raw, Vertex::Type::RESIDENT), resident_(raw)
{
}

void ResidentVertex::Print() const
{
  cout << "Resident Vertex: " << endl;
  Vertex::Print();
}

string ResidentVertex::GetName() const
{
  return resident_->GetName();
}

double ResidentVertex::GetConsumingPower() const
{
  return resident_->GetConsumingPower();
}

void ResidentVertex::SetSource(SourceVertex* source_vertex)
{
  source_vertex_ = source_vertex;
}

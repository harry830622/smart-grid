#include "switch_edge.hpp"

#include <iostream>

using namespace std;

SwitchEdge::SwitchEdge(Switch* raw) : Edge(raw, Edge::Type::SWITCH), switch_(raw)
{
}

void SwitchEdge::Print() const
{
  cout << "Switch Edge: " << endl;
  switch_->Print();
}

bool SwitchEdge::GetIsOn() const
{
  return switch_->GetIsOn();
}

void SwitchEdge::TurnOn()
{
  switch_->TurnOn();
}

void SwitchEdge::TurnOff()
{
  switch_->TurnOff();
}

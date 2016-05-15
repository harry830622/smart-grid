#include "pseudo_vertex.hpp"

using namespace std;

PseudoVertex::PseudoVertex(string name, Node::Type type, Vertex* source)
  : Node(name, type), graph_(new Graph), root_(source), power_(0.0)
{
}

PseudoVertex::~PseudoVertex()
{
  delete graph_;
  graph_ = nullptr;
}

Graph* PseudoVertex::GetGraph()
{
  return graph_;
}

Vertex* PseudoVertex::GetSource()
{
  return root_;
}

double PseudoVertex::GetPower()
{
  return power_;
}

void PseudoVertex::SetPower(double power)
{
  power_= power;
}

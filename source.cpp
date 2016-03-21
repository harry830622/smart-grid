#include "source.hpp"

Source::Source(std::string name, double power)
  :Node(name), power_(power)
{
}

void Source::Print()
{
  Node::Print();
}

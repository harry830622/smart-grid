#include "source.hpp"

#include <iostream>

using namespace std;

Source::Source(string name, double output_power)
  : Node(name, Node::Type::SOURCE), output_power_(output_power)
{
}

/* Source::~Source() */
/* { */
/*   cout << "Destruct Source" << endl; */
/* } */


void Source::Print() const
{
  Node::Print();
  cout << "Source: " << endl;
  cout << "  output_power: " << output_power_ << endl;
}

double Source::GetOutputPower() const
{
  return output_power_;
}

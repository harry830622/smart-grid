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
    cout << resident->GetName() << endl;
  }
}

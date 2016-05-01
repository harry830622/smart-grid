#include "smart_grid.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

SmartGrid::SmartGrid()
{
}

void SmartGrid::Print()
{
  for (auto pair : grids_) {
    pair.second.Print();
    cout << endl;
  }
}

Grid SmartGrid::GetGrid(char phase)
{
  return grids_.find(phase)->second;
}

#ifndef SMART_GRID_HPP
#define SMART_GRID_HPP

#include "grid.hpp"

#include <map>

class SmartGrid
{
  public:
    SmartGrid();

  private:
    std::map<char, Grid> grids_;

};

#endif

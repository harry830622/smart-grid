#ifndef SMART_GRID_HPP
#define SMART_GRID_HPP

#include "grid.hpp"

#include <iostream>
#include <map>

class SmartGrid
{
  public:
    SmartGrid();

    void Print();
    Grid GetGrid(char phase);
    void ParseNet(std::istream& input);
    void ParseGeo(std::istream& input);

  private:
    std::map<char, Grid> grids_;

};

#endif

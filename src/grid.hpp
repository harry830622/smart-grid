#ifndef GRID_HPP
#define GRID_HPP

#include "graph.hpp"

class Grid
{
  public:
    Grid(char phase);

  private:
    char phase_;
    Graph graph_;

};

#endif

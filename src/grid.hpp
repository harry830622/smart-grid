#ifndef GRID_HPP
#define GRID_HPP

#include "smart_grid.hpp"
#include "graph.hpp"

#include <fstream>

class SmartGrid;

class Grid
{
  public:
    Grid(SmartGrid* smart_grid, char phase);
    ~Grid();

    void Print() const;

    void ParseGrid(std::ifstream& input);

    char GetPhase() const;
    Graph* GetGraph() const;

  private:
    SmartGrid* smart_grid_;
    char phase_;
    Graph* graph_;

};

#endif

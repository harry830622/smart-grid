#ifndef GRID_HPP
#define GRID_HPP

#include "graph.hpp"
#include "source.hpp"
#include "resident.hpp"
#include "wire.hpp"
#include "switch.hpp"

class Grid
{
  public:
    Grid(char phase);
    ~Grid();

    void Print();
    char GetPhase();
    Graph GetGraph();

  private:
    char phase_;
    Graph graph_;
    std::map<std::string, Source*> sources_;
    std::map<std::string, Resident*> residents_;

};

#endif

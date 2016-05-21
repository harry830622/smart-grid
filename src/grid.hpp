#ifndef GRID_HPP
#define GRID_HPP

#include "smart_grid.hpp"
#include "graph.hpp"

#include <fstream>

class SmartGrid;
class Graph;
class Vertex;
class Edge;

class Grid
{
  public:
    Grid(SmartGrid* smart_grid, char phase);
    ~Grid();

    void Print() const;

    void ParseGrid(std::ifstream& input);
    void ShrinkGraph();

    SmartGrid* GetSmartGrid() const;

    char GetPhase() const;
    Graph* GetGraph() const;

    void AddVertex(Vertex* vertex);
    void AddEdge(Edge* edge);

  private:
    SmartGrid* smart_grid_;

    char phase_;

    std::map<Vertex*, Vertex*> all_vertices_;
    std::map<Edge*, Edge*> all_edges_;

    Graph* graph_;
    Graph* shrinked_graph_;

};

#endif

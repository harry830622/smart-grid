#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "grid.hpp"
#include "vertex.hpp"
#include "source_vertex.hpp"
#include "edge.hpp"

#include <map>

class Grid;

class Graph
{
  public:
    Graph(Grid* grid);
    ~Graph();

    void Print() const;

    Graph* Shrink();

    Vertex* GetVertex(std::string name) const;
    int GetVerticesNum() const;
    Edge* GetEdge(std::string name) const;

    Vertex* GetRoot() const;

    void SetRoot(Vertex* root);

    void AddVertex(Vertex* vertex);
    void AddEdge(Edge* edge);

  private:
    Grid* grid_;

    std::map<std::string, Vertex*> vertices_;
    std::map<std::string, Edge*> edges_;

    std::vector<SourceVertex*> source_vertices_;

    Vertex* root_;

    void ResetVerticesMarks();
    void MarkArticulationPoints();
    Graph* ShrinkByArticulationPoints();
    Graph* ShrinkBySwitches();

};

#endif

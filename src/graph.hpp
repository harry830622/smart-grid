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
    ~Graph() = default;

    void Print() const;
    void OutputJSON() const;

    Graph* Shrink();

    Vertex* GetVertex(std::string name) const;
    int GetVerticesNum() const;
    Edge* GetEdge(std::string name) const;

    Vertex* GetRoot() const;

    void SetRoot(Vertex* root);

    void AddVertex(Vertex* vertex);
    void AddEdge(Edge* edge);
    void SetApplySource();
    int GetSourceNum();
    void SetShrinkSource(); // set pseudo vertex which contains sources into source_vertices_
    Vertex* GetSource(int);
    void DeepSetApplySource(std::string="no assign");
    void CountCost();
    void Check ();

  private:
    Grid* grid_;

    std::map<std::string, Vertex*> vertices_;
    std::map<std::string, Edge*> edges_;

    std::vector<Vertex*> source_vertices_;
    std::map<std::string,double> remain_power_;

    Vertex* root_;

    void ResetVerticesMarks();
    void MarkArticulationPoints();
    Graph* ShrinkByArticulationPoints();
    Graph* ShrinkBySwitches();

    double wire_upgrade;
    int switch_change;
};

#endif

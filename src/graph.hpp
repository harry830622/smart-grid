#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "vertex.hpp"
#include "source_vertex.hpp"
#include "edge.hpp"

#include <map>

class Graph
{
  public:
    Graph();
    ~Graph();

    void Print() const;

    Graph* Shrink();

    Vertex* GetVertex(std::string name) const;
    int GetVerticesNum() const;
    Edge* GetEdge(std::string name) const;

    void AddVertex(Vertex* vertex);
    void AddEdge(Edge* edge);

  private:
    std::map<std::string, Vertex*> vertices_;
    std::map<std::string, Edge*> edges_;

    std::vector<SourceVertex*> source_vertices_;

    Vertex* root_;

    void ResetVerticesMarks();
    void DFS();
    void MarkArticulationPoints();
    void BFS();

};

#endif

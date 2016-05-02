#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "vertex.hpp"
#include "edge.hpp"

#include <map>

class Graph
{
  public:
    Graph();
    ~Graph();

    Vertex* GetVertex(std::string name) const;
    Edge* GetEdge(std::string name) const;
    void AddVertex(Vertex* vertex);
    void AddEdge(Edge* edge);

  private:
    std::map<std::string, Vertex*> vertices_;
    std::map<std::string, Edge*> edges_;

};

#endif

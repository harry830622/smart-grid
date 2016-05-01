#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "vertex.hpp"
#include "edge.hpp"

#include <string>
#include <map>

class Graph
{
  public:
    Graph();
    ~Graph();

    void Print();
    Vertex* GetVertex(std::string name);
    void AddVertex(Vertex* vertex);
    void AddEdge(Edge* edge);

  private:
    std::map<std::string, Vertex*> vertices_;
    std::map<std::string, Edge*> edges_;

};

#endif

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "node.hpp"
#include "edge.hpp"

#include <vector>

class Edge;

class Vertex
{
  public:
    Vertex(Node* raw);

    Node* GetRaw() const;
    void AddIncidentEdge(Edge* edge);

  private:
    Node* raw_;
    std::vector<Edge*> incident_edges_;

};

#endif

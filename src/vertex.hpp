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
    std::vector<Edge*> incident_edges_;

    Node* raw_;
    double voltage_;

};

#endif

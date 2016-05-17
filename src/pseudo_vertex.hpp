#ifndef PSEUDO_VERTEX_HPP
#define PSEUDO_VERTEX_HPP

#include "vertex.hpp"

#include <map>

class PseudoVertex : public Vertex
{
  public:
    PseudoVertex(Node* raw);

    virtual void Print() const;

    double GetConsumingPower() const;

    void AddBoundaryVertex(Edge* edge, Vertex* vertex);

  private:
    double consuming_power_;

    std::map<Edge*, Vertex*> boundary_vertices_; // Index by edge

};

#endif

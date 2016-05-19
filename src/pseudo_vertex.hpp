#ifndef PSEUDO_VERTEX_HPP
#define PSEUDO_VERTEX_HPP

#include "graph.hpp"

#include <map>

class Graph;

class PseudoVertex : public Vertex
{
  public:
    PseudoVertex(Node* raw);
    virtual ~PseudoVertex() = default;

    virtual void Print() const;

    void MergeDescendants(Vertex* root);

    double GetConsumingPower() const;

    Graph* GetGraph() const;

    void AddBoundaryVertex(Edge* edge, Vertex* vertex);

  private:
    double consuming_power_;

    Graph* graph_;
    std::map<Edge*, Vertex*> boundary_vertices_; // Index by edge

    Vertex* root_;

};

#endif

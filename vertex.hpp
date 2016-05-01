#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "node.hpp"
#include "edge.hpp"
#include "point.hpp"

#include <string>
#include <vector>

class Edge;

class Vertex
{
  public:
    Vertex(Node raw);

    void Print();
    Node GetRaw();
    Point GetCoordinate();
    void SetCoordinateX(double x);
    void SetCoordinateY(double y);
    void SetCoordinateZ(double z);
    void AddEdge(Edge* edge);

  private:
    Node raw_;
    std::vector<Edge*> edges_;
    Point coordinate_;

};

#endif

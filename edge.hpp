#ifndef EDGE_HPP
#define EDGE_HPP

#include "node.hpp"
#include "vertex.hpp"

#include <string>
#include <vector>

class Vertex;

class Edge
{
  public:
    Edge(Node* raw);
    ~Edge();

    void Print();
    Node* GetRaw();
    void AddVertex(Vertex* vertex);

  private:
    Node* raw_;
    std::vector<Vertex*> vertices_;

};

#endif

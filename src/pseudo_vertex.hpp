#ifndef PSEUDO_VERTEX_HPP
#define PSEUDO_VERTEX_HPP

#include "graph.hpp"

class PseudoVertex : public Node
{
  public:
    PseudoVertex(std::string name, Node::Type type, Vertex* source);
    ~PseudoVertex();

    Graph* GetGraph();
    Vertex* GetSource();
    double GetPower();

    void SetPower(double power);

  private:
    Graph* graph_;
    Vertex* root_;
    double power_;

};

#endif

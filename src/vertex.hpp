#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "node.hpp"
#include "edge.hpp"

#include <vector>

class Edge;

class Vertex
{
  public:
    enum class Type
    {
      VERTEX,
      SOURCE,
      RESIDENT
    };

    Vertex(Node* raw, Type type = Type::VERTEX);
    virtual ~Vertex() = default;

    virtual void Print() const;

    Node* GetRaw() const;
    Type GetType() const;
    void AddIncidentEdge(Edge* edge);

  private:
    std::vector<Edge*> incident_edges_;

    Node* raw_;
    Type type_;
    double voltage_;

};

#endif

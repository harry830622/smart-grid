#ifndef EDGE_HPP
#define EDGE_HPP

#include "wire.hpp"
#include "vertex.hpp"

#include <vector>

class Vertex;

class Edge
{
  public:
    enum class Type
    {
      EDGE,
      SWITCH
    };

    Edge(Wire* raw, Type type = Type::EDGE);
    virtual ~Edge() = default;

    virtual void Print() const;

    Wire* GetRaw() const;
    Type GetType() const;
    void AddIncidentVertex(Vertex* vertex);

  private:
    std::vector<Vertex*> incident_vertices_;

    Wire* raw_;
    Type type_;
    double current_;

};

#endif

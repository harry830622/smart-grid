#ifndef EDGE_HPP
#define EDGE_HPP

#include "wire.hpp"
#include "vertex.hpp"

#include <vector>

class Grid;
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

    Grid* GetGrid() const;

    Wire* GetRaw() const;
    Type GetType() const;
    double GetCurrent() const;

    Vertex* GetNeighbor(Vertex* vertex) const;

    void SetGrid(Grid* grid);

    void AddIncidentVertex(Vertex* vertex);

  private:
    Grid* grid_;

    Wire* raw_;
    Type type_;
    double current_;

    std::vector<Vertex*> incident_vertices_;

};

#endif

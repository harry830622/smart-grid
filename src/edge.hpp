#ifndef EDGE_HPP
#define EDGE_HPP

#include "wire.hpp"
#include "vertex.hpp"

#include <vector>

class Vertex;

class Edge
{
  public:
    Edge(Wire* raw);

    Wire* GetRaw() const;
    void AddIncidentVertex(Vertex* vertex);

  private:
    std::vector<Vertex*> incident_vertices_;

    Wire* raw_;
    double current_;

};

#endif

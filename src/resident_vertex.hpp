#ifndef RESIDENT_VERTEX_HPP
#define RESIDENT_VERTEX_HPP

#include "source_vertex.hpp"

class SourceVertex;

class ResidentVertex : public Vertex
{
  public:
    ResidentVertex(Resident* raw);
    virtual ~ResidentVertex() = default;

    virtual void Print() const;

    std::string GetName() const;
    double GetConsumingPower() const;

    void SetSource(SourceVertex* source_vertex);

  private:
    Resident* resident_;
    SourceVertex* source_vertex_;

};

#endif

#ifndef SOURCE_VERTEX_HPP
#define SOURCE_VERTEX_HPP

#include "vertex.hpp"
#include "source.hpp"
#include "resident_vertex.hpp"

#include <map>

class ResidentVertex;

class SourceVertex : public Vertex
{
  public:
    SourceVertex(Source* raw);
    virtual ~SourceVertex() = default;

    virtual void Print() const;

    double GetOutputPower() const;
    double GetLoadingPower() const;
    double GetRemainingPower() const;

    void AddLoadingResident(ResidentVertex* resident);

  private:
    Source* source_;
    std::map<std::string, ResidentVertex*> loading_residents_;

};

#endif

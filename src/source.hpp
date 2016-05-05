#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "node.hpp"
#include "resident.hpp"

class Resident;

class Source : public Node
{
  public:
    Source(std::string name, double output_power);
    virtual ~Source() = default;

    virtual void Print() const;

    double GetOutputPower() const;

  private:
    double output_power_;

};

#endif

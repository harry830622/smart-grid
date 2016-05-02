#ifndef RESIDENT_HPP
#define RESIDENT_HPP

#include "source.hpp"

class Source;

class Resident : public Node
{
  public:
    Resident(std::string name, double consuming_power);

    virtual void Print() const;

    double GetConsumingPower() const;

  private:
    double consuming_power_;

};

#endif

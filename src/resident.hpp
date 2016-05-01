#ifndef RESIDENT_HPP
#define RESIDENT_HPP

#include "source.hpp"

class Source;

class Resident : public Node
{
  public:
    Resident(std::string name, double consuming_power);

    double GetConsumingPower() const;
    void SetSource(Source* source);

  private:
    double consuming_power_;
    Source* source_;

};

#endif

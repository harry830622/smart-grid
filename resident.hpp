#ifndef RESIDENT_HPP
#define RESIDENT_HPP

#include "node.hpp"
#include "source.hpp"

#include <string>

class Source;

class Resident :public Node
{
  public:
    Resident(std::string name, double power);

    void Print() const;
    double GetPower() const;
    void SetSource(Source* source);

  private:
    double power_;
    Source* source_;

};

#endif

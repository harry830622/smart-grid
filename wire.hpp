#ifndef WIRE_HPP
#define WIRE_HPP

#include "node.hpp"

#include <limits>

class Wire :public Node
{
  public:
    Wire(std::string name, double resistence = 0.0, double current_limit = std::numeric_limits<double>::max());

    void Print() const;
    double GetResistence() const;
    double GetCurrentLimit() const;

  private:
    double resistence_;
    double current_limit_;

};

#endif

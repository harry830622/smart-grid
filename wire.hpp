#ifndef WIRE_HPP
#define WIRE_HPP

#include "node.hpp"

class Wire :public Node
{
  public:
    Wire(std::string name, double resistence = 0.0, double current_limit = -1.0);

  private:
    double resistence_;
    double current_limit_;

};

#endif

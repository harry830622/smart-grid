#include "wire.hpp"

Wire::Wire(std::string name, double resistence, double current_limit)
  :Node(name), resistence_(resistence), current_limit_(current_limit)
{
}

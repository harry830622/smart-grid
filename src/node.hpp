#ifndef NODE_HPP
#define NODE_HPP

#include "equipment.hpp"
#include "point.hpp"

class Node : public Equipment
{
  public:
    enum class Type
    {
      NODE,
      SOURCE,
      RESIDENT
    };

    Node(std::string name, Type type);

    Point GetCoordinate() const;

  private:
    Type type_;
    Point coordinate_;

};

#endif

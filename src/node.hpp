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

    Node(std::string name, Type type = Type::NODE);
    virtual ~Node() = default;

    virtual void Print() const;

    Type GetType() const;
    Point GetCoordinate() const;

    void SetCoordinateX(double x);
    void SetCoordinateY(double y);
    void SetCoordinateZ(double z);

  private:
    Type type_;
    Point coordinate_;

};

#endif

#ifndef WIRE_HPP
#define WIRE_HPP

#include "equipment.hpp"

#include <limits>

class Wire : public Equipment
{
  public:
    enum class Type
    {
      WIRE,
      SWITCH
    };

    Wire(std::string name, Type type = Type::WIRE, double resistance = 0.0, double current_limit = std::numeric_limits<double>::max());

    virtual void Print() const;

    double GetResistance() const;
    double GetCurrentLimit() const;

  protected:
    void SetCurrentLimit(double current_limit);

  private:
    Type type_;
    double resistance_;
    double current_limit_;

};

#endif

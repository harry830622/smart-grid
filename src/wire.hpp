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

    constexpr static const double IDEAL_RESISTENCE = 0.0;
    constexpr static const double IDEAL_CURRENT_LIMIT = std::numeric_limits<double>::max();

    Wire(std::string name, double resistance = 0.0, double current_limit = std::numeric_limits<double>::max(),
        Type type = Type::WIRE);
    virtual ~Wire() = default;

    virtual void Print() const;

    Type GetType() const;
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

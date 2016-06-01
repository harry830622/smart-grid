#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP

#include <string>

class Equipment
{
  public:
    enum class Type
    {
      EQUIPMENT,
      NODE,
      WIRE
    };

    Equipment(std::string name, Type type = Type::EQUIPMENT);
    virtual ~Equipment() = default;

    virtual void Print() const;

    Type GetType() const;
    std::string GetName() const;

  private:
    Type type_;
    std::string name_;

};

#endif

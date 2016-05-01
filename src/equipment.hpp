#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP

#include <string>

class Equipment
{
  public:
    Equipment(std::string name);

    std::string GetName() const;

  private:
    std::string name_;

};

#endif

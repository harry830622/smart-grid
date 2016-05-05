#ifndef SWITCH_HPP
#define SWITCH_HPP

#include "wire.hpp"

class Switch : public Wire
{
  public:
    Switch(std::string name, bool is_on = false);
    virtual ~Switch() = default;

    virtual void Print() const;

    bool GetIsOn() const;
    void SetIsOn(bool is_on = true);
    void TurnOn();
    void TurnOff();

  private:
    bool is_on_;

};

#endif

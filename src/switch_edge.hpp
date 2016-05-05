#ifndef SWITCH_EDGE_HPP
#define SWITCH_EDGE_HPP

#include "edge.hpp"
#include "switch.hpp"

class SwitchEdge : public Edge
{
  public:
    SwitchEdge(Switch* raw);
    virtual ~SwitchEdge() = default;

    virtual void Print() const;

    bool GetIsOn() const;
    void TurnOn();
    void TurnOff();

  private:
    Switch* switch_;

};

#endif

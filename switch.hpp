#ifndef SWITCH_HPP
#define SWITCH_HPP

#include "node.hpp"

class Switch :public Node
{
  public:
    Switch(std::string name, bool is_on);

    void Print() const;
    bool GetIsOn() const;
    void SetIsOn(bool is_on = true);

  private:
    bool is_on_;

};

#endif

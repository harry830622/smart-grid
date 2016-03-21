#ifndef NODE_HPP
#define NODE_HPP

#include <string>

class Node
{
  public:
    Node(std::string name);
    virtual ~Node();

    virtual void Print();
    char GetPhase();

  private:
    std::string name_;
    char phase_;

};

#endif

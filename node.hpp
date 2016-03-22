#ifndef NODE_HPP
#define NODE_HPP

#include <string>

class Node
{
  public:
    enum class Type
    {
      NODE,
      SOURCE,
      RESIDENT,
      WIRE,
      SWITCH
    };

    Node(std::string name, Type type = Type::NODE);
    virtual ~Node();

    virtual void Print();
    Type GetType();
    std::string GetName();
    char GetPhase();

  private:
    Type type_;
    std::string name_;
    char phase_;

};

#endif

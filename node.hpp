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

    virtual void Print() const;
    Type GetType() const;
    std::string GetName() const;

  private:
    std::string name_;
    Type type_;

};

#endif

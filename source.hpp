#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "node.hpp"
#include "resident.hpp"

#include <string>
#include <vector>

class Resident;

class Source :public Node
{
  public:
    Source(std::string name, double power = 0.0);

    void Print();
    double RemainingPower();
    void AddLoadingResident(Resident* resident);

  private:
    double power_;
    std::vector<Resident*> loading_residents_;

};

#endif

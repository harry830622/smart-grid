#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "node.hpp"
#include "resident.hpp"

#include <string>
#include <map>

class Resident;

class Source :public Node
{
  public:
    Source(std::string name, double power = 0.0);

    void Print() const;
    double GetPower() const;
    double LoadingPower() const;
    double RemainingPower() const;
    void AddLoadingResident(Resident* resident);

  private:
    double power_;
    std::map<std::string, Resident*> loading_residents_;

};

#endif

#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "node.hpp"
#include "resident.hpp"

#include <map>

class Resident;

class Source : public Node
{
  public:
    Source(std::string name, double output_power);

    double GetOutputPower() const;
    double LoadingPower() const;
    double RemainingPower() const;
    void AddLoadingResident(Resident* resident);

  private:
    double output_power_;
    std::map<std::string, Resident*> loading_residents_;

};

#endif

#ifndef POWER_STATION_HPP
#define POWER_STATION_HPP

#include "vertex.hpp"
#include "resident.hpp"

#include <map>

class PowerStation : public Vertex
{
  public:
    PowerStation(Source* raw);

    double OutputPower() const;
    double LoadingPower() const;
    double RemainingPower() const;
    void AddLoadingResident(Resident* resident);

  private:
    Source* source_;
    std::map<std::string, Resident* const> loading_residents_;

};

#endif

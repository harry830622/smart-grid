#ifndef SMART_GRID_HPP
#define SMART_GRID_HPP

#include "grid.hpp"

#include <iostream>
#include <map>

class SmartGrid
{
  public:
    SmartGrid();
    ~SmartGrid();

    void PrintEquipments() const;

    void ParseEquipments(std::istream& input);

  private:
    std::map<std::string, Equipment*> equipments_;
    std::map<char, Grid> grids_;

};

#endif

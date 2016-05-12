#ifndef SMART_GRID_HPP
#define SMART_GRID_HPP

#include "grid.hpp"
#include "equipment.hpp"

#include <fstream>
#include <map>

class Grid;

class SmartGrid
{
  public:
    SmartGrid();
    ~SmartGrid();

    void PrintEquipments() const;
    void PrintGrids() const;

    void Parse(std::ifstream& equipments_data_input, std::ifstream& node_coordinates_input, std::ifstream& grids_wrapper_input);

    Equipment* GetEquipment(std::string name) const;
    void AddEquipment(Equipment* equipment);
    Grid* GetGrid (char);
    

  private:
    void ParseEquipments(std::ifstream& input);
    void ParseNodeCoordinates(std::ifstream& input);
    void ParseGrids(std::ifstream& input);

    std::map<std::string, Equipment*> equipments_;
    std::map<char, Grid*> grids_;

};

#endif

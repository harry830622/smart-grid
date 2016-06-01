#ifndef SMART_GRID_HPP
#define SMART_GRID_HPP

#include "grid.hpp"
#include "equipment.hpp"

#include <fstream>
#include <map>

class Grid;

// It's a container at the top of the hierarchy used for parsing and operating on grids. It's responsible for managing
// the lifecycles of all equipments and grids inside.
class SmartGrid
{
  public:
    SmartGrid();
    ~SmartGrid();

    void PrintEquipments() const;
    void PrintGrids() const;

    // Parse all the files including equipments' informations, nodes' coordinates and grids' data at each phase.
    void Parse(std::ifstream& equipments_data_input, std::ifstream& node_coordinates_input, std::ifstream& grids_wrapper_input);

    /* void DistributePowerForGrids(); */
    /* void DistributePowerForGrid(char phase); */

    // Notice that a getter will return a null pointer if the target is not found.
    Equipment* GetEquipment(std::string name) const;
    Grid* GetGrid(char phase) const;

    void AddEquipment(Equipment* equipment);

  private:
    std::map<std::string, Equipment*> equipments_;
    std::map<char, Grid*> grids_;

    void ParseEquipments(std::ifstream& input);
    void ParseNodeCoordinates(std::ifstream& input);
    void ParseGrids(std::ifstream& input);

};

#endif

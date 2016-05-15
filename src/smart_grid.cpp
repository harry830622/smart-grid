#include "smart_grid.hpp"

#include "switch.hpp"
#include "source.hpp"
#include "resident.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

SmartGrid::SmartGrid()
{
}

SmartGrid::~SmartGrid()
{
  for (auto pair : equipments_) {
    delete pair.second;
    pair.second = nullptr;
  }
  for (auto pair : grids_) {
    delete pair.second;
    pair.second = nullptr;
  }
}

void SmartGrid::PrintEquipments() const
{
  for (auto pair : equipments_) {
    pair.second->Print();
    cout << endl;
  }
}

void SmartGrid::PrintGrids() const
{
  for (auto pair : grids_) {
    pair.second->Print();
    cout << endl;
  }
}

void SmartGrid::Parse(ifstream& equipments_data_input, ifstream& node_coordinates_input, ifstream& grids_wrapper_input)
{
  ParseEquipments(equipments_data_input);
  ParseNodeCoordinates(node_coordinates_input);
  ParseGrids(grids_wrapper_input);
}

Equipment* SmartGrid::GetEquipment(string name) const
{
  if (equipments_.find(name) == equipments_.end()) {
    return nullptr;
  }

  return equipments_.find(name)->second;
}

void SmartGrid::AddEquipment(Equipment* equipment)
{
  equipments_.insert(make_pair(equipment->GetName(), equipment));
}

void SmartGrid::ParseEquipments(ifstream& input)
{
  string line_str;
  while (getline(input, line_str)) {
    stringstream line_ss(line_str);

    string type;
    line_ss >> type;

    string name;
    line_ss >> name;

    Equipment* equipment;
    if (type == "node") {
      equipment = new Node(name);
    } else if (type == "source") {
      double output_power;
      line_ss >> output_power;

      equipment = new Source(name, output_power);
    } else if (type == "resid") {
      double consuming_power;
      line_ss >> consuming_power;

      equipment = new Resident(name, consuming_power);
    } else if (type == "wire") {
      double resistance;
      line_ss >> resistance;

      double current_limit;
      line_ss >> current_limit;

      equipment = new Wire(name, Wire::Type::WIRE, resistance, current_limit);
    } else if (type == "i_wire") {
      equipment = new Wire(name);
    } else if (type == "switch") {
      string is_on_str;
      line_ss >> is_on_str;

      bool is_on = false;
      if (is_on_str == "on") {
        is_on = true;
      }

      equipment = new Switch(name, is_on);
    } else {
      continue;
    }
    equipments_.insert(make_pair(equipment->GetName(), equipment));
  }
}

void SmartGrid::ParseNodeCoordinates(ifstream& input)
{
  string line_str;
  while (getline(input, line_str)) {
    stringstream line_ss(line_str);

    string name;
    line_ss >> name;

    assert(equipments_.find(name) != equipments_.end());
    Node* node = dynamic_cast<Node*>(equipments_.find(name)->second);

    double x;
    line_ss >> x;

    double y;
    line_ss >> y;

    double z;
    line_ss >> z;

    node->SetCoordinateX(x);
    node->SetCoordinateY(y);
    node->SetCoordinateZ(z);
  }
}

void SmartGrid::ParseGrids(ifstream& input)
{
  string line_str;
  while (getline(input, line_str)) {
    stringstream line_ss(line_str);

    char phase;
    line_ss >> phase;

    string grid_input_name;
    line_ss >> grid_input_name;

    Grid* grid = new Grid(this, phase);
    grids_.insert(make_pair(phase, grid));

    ifstream grid_input(grid_input_name.c_str());
    grid->ParseGrid(grid_input);
  }
}

Grid*  SmartGrid::GetGrid(char c){
	return grids_[c];
}

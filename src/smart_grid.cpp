#include "smart_grid.hpp"

#include "switch.hpp"
#include "source.hpp"
#include "resident.hpp"

#include <cassert>
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
}

void SmartGrid::PrintEquipments() const
{
  for (auto pair : equipments_) {
    pair.second->Print();
    cout << endl;
  }
}

void SmartGrid::ParseEquipments(istream& input)
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
      cout << "Type: " << type << " does not exist!" << endl;
      equipment = nullptr;
      assert(false);
    }
    equipments_.insert(make_pair(equipment->GetName(), equipment));
  }
}

#include "smart_grid.hpp"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " equipments.data nodes.pos grids.wrapper" << endl;
    return 1;
  }

  SmartGrid smart_grid;

  ifstream equipments_data_input(argv[1]);
  smart_grid.ParseEquipments(equipments_data_input);

  ifstream node_coordinates_input(argv[2]);
  smart_grid.ParseNodeCoordinates(node_coordinates_input);

  ifstream grids_wrapper_input(argv[3]);
  smart_grid.ParseGrids(grids_wrapper_input);

  /* smart_grid.PrintEquipments(); */
  smart_grid.PrintGrids();

  return 0;
}

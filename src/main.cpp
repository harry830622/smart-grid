#include "smart_grid.hpp"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
  // Check if the arguments for this program are acceptable. However, the truth is that it only checks if the number of
  // the arguments is correct, so the order and the file of the arguments must be check manually to make this program
  // behave correctly.
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " equipments.data nodes.pos grids.wrapper" << endl;
    return 1;
  }

  SmartGrid smart_grid;

  ifstream equipments_data_input(argv[1]);
  ifstream node_coordinates_input(argv[2]);
  ifstream grids_wrapper_input(argv[3]);

  smart_grid.Parse(equipments_data_input, node_coordinates_input, grids_wrapper_input);

  smart_grid.GetGrid('A')->ShrinkGraph();
  //smart_grid.GetGrid('B')->ShrinkGraph();
  //smart_grid.GetGrid('C')->ShrinkGraph();

  smart_grid.GetGrid('A')->GetShrinkGraph()->SetApplySource();
  smart_grid.GetGrid('A')->GetGraph()->CountCost();

  /* smart_grid.GetGrid('A')->GetGraph()->OutputJSON(); */

  /* smart_grid.PrintEquipments(); */
  /* smart_grid.PrintGrids(); */

  return 0;
}

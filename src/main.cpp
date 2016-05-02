#include "smart_grid.hpp"

#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " equipments.data nodes.pos grid.net" << endl;
    return 1;
  }

  SmartGrid smart_grid;

  ifstream equipments_data_input(argv[1]);
  smart_grid.ParseEquipments(equipments_data_input);

  smart_grid.PrintEquipments();

  return 0;
}

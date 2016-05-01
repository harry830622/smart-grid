#include "smart_grid.hpp"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " grid.net vertices.geo" << endl;
    return 1;
  }

  SmartGrid smart_grid;

  ifstream net_input(argv[1]);
  smart_grid.ParseNet(net_input);

  smart_grid.Print();

  return 0;
}

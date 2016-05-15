#include "smart_grid.hpp"
#include "pseudo_vertex.hpp"
#include "function.hpp"

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
  ifstream node_coordinates_input(argv[2]);
  ifstream grids_wrapper_input(argv[3]);

  smart_grid.Parse(equipments_data_input, node_coordinates_input, grids_wrapper_input);

  /* smart_grid.PrintEquipments(); */
  //smart_grid.PrintGrids();

  Graph* graph = smart_grid.GetGrid('A')->GetGraph();
  Graph* new_graph = new Graph;
  Vertex* root = nullptr;

  cout << "Old: " << graph->GetVertexNum() << endl;

  if (!graph->GetSource(root)) {
    cout << "GETDIEEEE!!!" << endl;
  } else {
    get_shrink_graph(root, graph, new_graph);
  }

  //new_graph -> Print();
  if (new_graph->GetVertex("N9933")->GetType() == Vertex::Type::PSEUDO) {
    PseudoVertex* temp_vertex = dynamic_cast<PseudoVertex*>(new_graph->GetVertex("N9933")->GetRaw());
    cout << "psuedo num: " << temp_vertex->GetGraph()->GetVertexNum() << endl;
  }

  cout << "Shrink: " << new_graph->GetVertexNum() << endl;

  return 0;
}

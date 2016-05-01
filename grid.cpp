#include "grid.hpp"

#include <iostream>

using namespace std;

Grid::Grid(char phase) :phase_(phase), graph_(new Graph())
{
}

Grid::~Grid()
{
  delete graph_;
  graph_ = nullptr;
}

void Grid::Print()
{
  cout << "Phase: " << phase_ << endl;
  graph_->Print();
}

Graph* Grid::GetGraph()
{
  return graph_;
}

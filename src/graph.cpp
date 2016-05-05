#include "graph.hpp"

#include <iostream>

using namespace std;

Graph::Graph()
{
}

Graph::~Graph()
{
  for (auto pair : vertices_) {
    delete pair.second;
    pair.second = nullptr;
  }
  for (auto pair : edges_) {
    delete pair.second;
    pair.second = nullptr;
  }
}

void Graph::Print() const
{
  cout << "Graph: " << endl;
  for (auto pair : vertices_) {
    pair.second->Print();
    cout << endl;
  }
  for (auto pair : edges_) {
    pair.second->Print();
    cout << endl;
  }
}

Vertex* Graph::GetVertex(std::string name) const
{
  if (vertices_.find(name) == vertices_.end()) {
    return nullptr;
  }

  return vertices_.find(name)->second;
}

Edge* Graph::GetEdge(std::string name) const
{
  if (edges_.find(name) == edges_.end()) {
    return nullptr;
  }

  return edges_.find(name)->second;
}

void Graph::AddVertex(Vertex* vertex)
{
  vertices_.insert(make_pair(vertex->GetRaw()->GetName(), vertex));
}

void Graph::AddEdge(Edge* edge)
{
  edges_.insert(make_pair(edge->GetRaw()->GetName(), edge));
}

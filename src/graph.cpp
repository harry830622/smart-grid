#include "graph.hpp"

#include <iostream>

using namespace std;

Graph::Graph()
{
	
}

Graph::~Graph()
{
  
    for (auto pair : vertices_) {
	if (pair.second != nullptr){
      		delete pair.second;
      		pair.second = nullptr;
	}
    }
    for (auto pair : edges_) {
	if (pair.second != nullptr){
      		delete pair.second;
      		pair.second = nullptr;
	}
    }
  
}

void Graph::Print() const
{
  cout << "Graph: "<<   endl;
  for (auto pair : vertices_) {
    if (pair.second == nullptr){
	cout << "Vertex wrong!!!";
	break;
    }
    pair.second->Print();
    cout << endl;
  }
  for (auto pair : edges_) {
    if (pair.second == nullptr){
	cout << "Edge wrong!!!";
	break;
    } 
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
  if (vertex->GetType() == Vertex::Type::SOURCE)
	sources_.push_back(vertex);
}

void Graph::AddEdge(Edge* edge)
{
  edges_.insert(make_pair(edge->GetRaw()->GetName(), edge));
}

int Graph::GetVertexNum(){
	return vertices_.size();
}

void Graph::FlushVertexMark() {
	for (auto pair : vertices_){
		pair.second->SetVisit(false);
		pair.second->index_num_=0;
		pair.second->low_=0;
		pair.second->SetIsArtic(false);
	}
}

void Graph::FlushVisit() {
	for (auto pair : vertices_){
		pair.second->SetVisit(false);
	}
}

bool Graph::GetSource (Vertex* &Source) {
    for (auto pair :vertices_) {
	if (pair.second->GetType() == Vertex::Type::SOURCE){
		 Source = pair.second;
		return true;
	}
    }
    return false;
}

Vertex* Graph::GetSource (int index){
	return sources_[index];
}
int Graph::GetSourceNum (){
	return sources_.size();
}

void Graph::SetVertexArtic(){
    for (auto pair : vertices_) {
	for (int j=0; j < pair.second->GetChildNum() ;++j){
		if (pair.second->GetChild(j)->low_ >= pair.second->index_num_ ){
			pair.second->SetIsArtic(true);
			break;
		}else
			pair.second->SetIsArtic(false);
	}
    }
}

#include "vertex.hpp"
#include "edge.hpp"
#include <iostream>

using namespace std;

Vertex::Vertex(Node* raw, Type type) : raw_(raw), type_(type), voltage_(0.0)
{
	visit_=false;
    	index_num_=0;
	low_=0;
	is_artic_=false;
}

void Vertex::Print() const
{
  cout << "Vertex: " << endl;
  raw_->Print();
}

Node* Vertex::GetRaw() const
{
  return raw_;
}

Vertex::Type Vertex::GetType() const
{
  return type_;
}

void Vertex::AddIncidentEdge(Edge* edge)
{
  incident_edges_.push_back(edge);
}

int Vertex::GetIncidentEdgeNum()
{
  return incident_edges_.size();
}

Edge* Vertex::GetIncidentEdge (int i){
  return incident_edges_[i];
}

double Vertex::GetVoltage () {
	return voltage_;
}

bool Vertex::GetVisit(){
	return visit_;
}

void Vertex::SetVisit(bool in){
	visit_ = in;
}
Vertex* Vertex::GetParant(){
	return parant_;
}
void Vertex::SetParant (Vertex* in){
	parant_ = in;
}
void Vertex::AddChild (Vertex* in){
	children_.push_back(in);
}
Vertex* Vertex::GetChild (int i){
	return children_[i];
}

int Vertex::GetChildNum (){
	return children_.size();
}
bool Vertex::GetIsArtic(){
	return is_artic_;
}

void Vertex::SetIsArtic(bool in){
	is_artic_ = in;
}


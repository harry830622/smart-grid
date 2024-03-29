#include "vertex.hpp"
#include "edge.hpp"

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

Vertex::Vertex(Node* raw, Type type)
  : grid_(nullptr), raw_(raw), type_(type), voltage_(0.0), parent_(nullptr), depth_(-1), low_(-1), is_articulate_(false), assign_source_("ungiven"), is_source_(false)
{
}

void Vertex::Print() const
{
  cout << "Vertex: " << endl;
  cout << "  depth_: " << depth_ << endl;
  cout << "  low_: " << low_ << endl;
  cout << "  is_articulate_: " << is_articulate_ << endl;
  cout << "  incident_edges_: " <<endl;
  cout << "  assign_source : " << assign_source_ << endl;
  for (auto edge : incident_edges_) {
    cout << edge->GetRaw()->GetName() << " ";
  }
  cout << endl;
  raw_->Print();
}

Grid* Vertex::GetGrid() const
{
  return grid_;
}

Node* Vertex::GetRaw() const
{
  return raw_;
}

Vertex::Type Vertex::GetType() const
{
  return type_;
}

double Vertex::GetVoltage() const
{
  return voltage_;
}

int Vertex::GetIncidentEdgesNum() const
{
  return incident_edges_.size();
}

Edge* Vertex::GetIncidentEdge(int idx) const
{
  assert(idx < incident_edges_.size());

  return incident_edges_[idx];
}

bool Vertex::GetIsVisited() const
{
  return depth_ != -1;
}

Vertex* Vertex::GetParent() const
{
  return parent_;
}

int Vertex::GetChildrenNum() const
{
  return children_.size();
}

Vertex* Vertex::GetChild(int idx) const
{
  return children_[idx];
}

int Vertex::GetDepth() const
{
  return depth_;
}

int Vertex::GetLow() const
{
  return low_;
}

int Vertex::GetIsArticulate() const
{
  return is_articulate_;
}

void Vertex::SetGrid(Grid* grid)
{
  grid_ = grid;
}

void Vertex::SetIncidentEdge(int idx, Edge* incident_edge)
{
  assert(idx < incident_edges_.size());

  incident_edges_[idx] = incident_edge;
}

void Vertex::SetIsVisted(bool is_visited)
{
  if (is_visited) {
    depth_ = 0;
  } else {
    depth_ = -1;
  }
}

void Vertex::SetParent(Vertex* parent)
{
  parent_ = parent;
}

void Vertex::SetDepth(int depth)
{
  depth_ = depth;
}

void Vertex::SetLow(int low)
{
  low_ = low;
}

void Vertex::SetIsArticulate(bool is_articulate)
{
  is_articulate_ = is_articulate;
}

void Vertex::AddIncidentEdge(Edge* edge)
{
  incident_edges_.push_back(edge);
}

void Vertex::AddChild(Vertex* child)
{
  children_.push_back(child);
}

// Reset all marks to default value except for low_ and is_articulate_
void Vertex::ResetMarks()
{
  parent_ = nullptr;
  children_.clear();
  depth_ = -1;
  parent_edge_ = nullptr;
}

void Vertex::SetSourceDistance (Vertex* vertex, int distance){
	source_distance_[vertex]=distance;
}
int Vertex::GetSourceDistance (Vertex* vertex){
	if (source_distance_.find(vertex) == source_distance_.end() )
		return -1;
	else return source_distance_[vertex];
}
void Vertex::SetAssignSource (std::string input){
	assign_source_ = input;
}

std::string Vertex::GetAssignSource(){ 
	return assign_source_;
}
bool priority_compare(pair<Vertex*, int> a, pair<Vertex*, int> b){
	return (a.second < b.second);
}

void Vertex::CountDistanceDiff (){
	int min=-1, second=-1;
	for (auto pair:source_distance_){
		source_priority_.push_back(pair);
		if (min==-1){
			min = pair.second;
			second = pair.second;
		}else if (min > pair.second){
			second = min;
			min = pair.second;
		} else if (second > pair.second){
			second = pair.second;
		}
	}
	distance_diff_=second - min;
	assert(distance_diff_ >= 0 );

	sort(source_priority_.begin(), source_priority_.end(), priority_compare);
}

int Vertex::GetDistanceDiff (){
	return distance_diff_;
}
Vertex* Vertex::GetSourcePriority (int index){
	return source_priority_[index].first;
}
int Vertex::GetPriorityNum (){
	return source_priority_.size();
}

void Vertex::SetIsSource (bool input){
	is_source_ = input;
}

bool Vertex::GetIsSource(){ 
	return is_source_;
}

void Vertex::SetVoltage(double input){
	voltage_ = input;
}

double Vertex::GetVoltage(){
	return voltage_;
}

void Vertex::SetParentEdge(Edge* input){
	parent_edge_ = input;
}

Edge* Vertex::GetParentEdge(){
	return parent_edge_;
}

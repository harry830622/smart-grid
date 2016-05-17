#include "vertex.hpp"
#include "edge.hpp"

#include <cassert>
#include <iostream>

using namespace std;

Vertex::Vertex(Node* raw, Type type)
  : raw_(raw), type_(type), voltage_(0.0), parent_(nullptr), children_num_(0), depth_(-1), low_(-1), is_articulate_(false)
{
}

void Vertex::Print() const
{
  cout << "Vertex: " << endl;
  cout << "  depth_: " << depth_ << endl;
  cout << "  low_: " << low_ << endl;
  cout << "  is_articulate_: " << is_articulate_ << endl;
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

Vertex* Vertex::GetParent() const
{
  return parent_;
}

bool Vertex::GetIsDFSRoot() const
{
  return parent_ == nullptr;
}

int Vertex::GetChildrenNum() const
{
  return children_num_;
}

int Vertex::GetDepth() const
{
  return depth_;
}

int Vertex::GetLow() const
{
  return low_;
}

bool Vertex::GetIsVisited() const
{
  return depth_ != -1;
}

int Vertex::GetIsArticulate() const
{
  return is_articulate_;
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

void Vertex::IncrementChildrenNum()
{
  ++children_num_;
}

// Reset all marks to default value except for is_articulate_
void Vertex::ResetMarks()
{
  parent_ = nullptr;
  children_num_ = 0;
  depth_ = -1;
  low_ = -1;
}

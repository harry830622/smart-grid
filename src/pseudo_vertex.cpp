#include "pseudo_vertex.hpp"
#include "graph.hpp"
#include "vertex.hpp"
#include "node.hpp"

Pseudo_vertex :: Pseudo_vertex (std::string name, Node::Type type,Vertex* source) : Node(name, type), graph_(new Graph), root_(source), power_(0.0){}

Pseudo_vertex::~Pseudo_vertex (){
	delete graph_;
  	graph_ = nullptr;
}



Graph* Pseudo_vertex :: GetGraph () {
	return graph_;
}

Vertex* Pseudo_vertex:: GetSource () {
	return root_;


}

double Pseudo_vertex::GetPower(){
	return power_;
}

void Pseudo_vertex::SetPower(double pow){
	power_=pow;
}

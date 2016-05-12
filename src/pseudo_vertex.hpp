#ifndef PSEUDO_VERTEX_HPP
#define PSEUDO_VERTEX_HPP

#include "graph.hpp"
#include "vertex.hpp"
#include "node.hpp"
#include <string>
#include <map>
#include <vector>

class Pseudo_vertex : public Node {
	public:
		Pseudo_vertex(std::string name, Node::Type type,Vertex* source);
		~Pseudo_vertex();
		Graph* GetGraph();	
		Vertex* GetSource();
		double GetPower();
		void SetPower(double);
		
	private:
		Graph* graph_;
		Vertex* root_;
		double power_;
};






#endif

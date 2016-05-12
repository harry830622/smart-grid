#include "smart_grid.hpp"
#include "function.hpp"
#include "graph.hpp"
#include "pseudo_vertex.hpp"
#include "resident.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <queue>
void get_shrink_graph (Vertex* root, Graph* in_graph, Graph* new_graph) {
	in_graph->FlushVertexMark();
	std::stack <Vertex*> vertex_stack;
	vertex_stack.push(root);
	int index=0;
	root->low_=0;
	root->index_num_=0;
	
	while (!vertex_stack.empty()) { //dfs
		Vertex* source = vertex_stack.top();
		
		source->SetVisit(true);
		//source->index_num_=index;
		//cout <<index <<endl;
		//source->low_ = index;
		bool have_back_edge = false;
		
		
		for (int i=0;i<source->GetIncidentEdgeNum();++i) { // check back edge
			//cout <<"test"<<endl;
			if ( has_back_edge(source, source->GetIncidentEdge(i)->GetAnotherVertex(source), root)) {
				//cout <<"test1"<<endl;
				have_back_edge =true;
				if (source->low_ > source->GetIncidentEdge(i)->GetAnotherVertex(source)->low_){
					source->low_ = source->GetIncidentEdge(i)->GetAnotherVertex(source)->low_;
				}
			}
			//cout <<"test2"<<endl;
		}
		
		if (have_back_edge) {
			trace_back_setup(source, root);
		}
		
		bool all_visit = true;
		for (int i=0;i<source->GetIncidentEdgeNum();++i) { //get new member
			if (!source->GetIncidentEdge(i)->GetAnotherVertex(source)->GetVisit()) {
				all_visit = false;
				//cout << "DFS ADD" <<endl;
				Vertex* target = source->GetIncidentEdge(i)->GetAnotherVertex(source);
				target->SetParant (source);
				source->AddChild(target);
				vertex_stack.push(target);
				target->index_num_=++index;
				target->low_ = index;
				target->SetVisit(true);
				break;
			}else {
				continue;
			}
		}
		if (all_visit)
			vertex_stack.pop();
	}

	in_graph->SetVertexArtic();
	//==============================================================
	//find non-boundary artic
	//==============================================================
	
	//cout <<"break"<<endl;
	for (int i=0;i<in_graph->GetSourceNum();++i){
		Vertex* now = in_graph->GetSource(i);
		Vertex* parant;
		while (now!=root){
			parant=now->GetParant();
			now->SetIsArtic(false);
			now=parant;
		}
	}
	//cout <<"break"<<endl;
	//==============================================================
	//get new graph
	//==============================================================
	in_graph->FlushVisit();
	std::vector <Vertex*> v_artic_point;
	std::queue<Vertex*> q_vertex;
	root -> SetVisit(true);
	q_vertex.push(root);	
	new_graph->AddVertex(root);
	//new_graph = new Graph; // new a graph mem
	while (!q_vertex.empty()) {
		Vertex * source;
		source=q_vertex.front();
		
		q_vertex.pop();
		for (int i=0;i<source->GetIncidentEdgeNum();++i) {
			new_graph->AddEdge(source->GetIncidentEdge(i));
			Vertex* target = source->GetIncidentEdge(i)->GetAnotherVertex(source);
			if (!target->GetVisit()){
				target->SetVisit(true);
				if (target->GetIsArtic()){
					v_artic_point.push_back(target);
				}else{
					new_graph->AddVertex(target);
					q_vertex.push(target);
				}
			}		
		}
	}
	

	//==============================================================
	//merge
	//==============================================================
	for (int i=0; i<v_artic_point.size();++i){ // get articulation point to pseudo vertex;
		q_vertex.push(v_artic_point[i]);
		v_artic_point[i]->SetVisit(true);
		Pseudo_vertex * pseudo = new Pseudo_vertex(v_artic_point[i]->GetRaw()->GetName(), Node::Type::PSEUDO, v_artic_point[i]);
		Vertex* pseudo_vertex = new Vertex (pseudo, Vertex::Type::PSEUDO);
		pseudo->GetGraph()->AddVertex(v_artic_point[i]);
		pseudo->SetPower(0);
		while (!q_vertex.empty()) {
			Vertex * source;
			source=q_vertex.front();
			q_vertex.pop();

			for (int j=0;j<source->GetIncidentEdgeNum();++j){
				Vertex*target = source->GetIncidentEdge(j)->GetAnotherVertex(source);
				if (source==v_artic_point[i] && target->GetVisit()){
					continue;
				}
				
				pseudo->GetGraph()->AddEdge(source->GetIncidentEdge(j));
				if (!target->GetVisit()) {
					pseudo->GetGraph()->AddVertex(target);
					if (target->GetType()==Vertex::Type::SOURCE) {
						std::cout << "These is a source in pseudo_vertex!"<<std::endl;
					} else if (target->GetType()==Vertex::Type::RESIDENT){
						pseudo->SetPower(pseudo->GetPower()+dynamic_cast<Resident*>(target->GetRaw())->GetConsumingPower());
					}
					target->SetVisit(true);
					q_vertex.push(target);
				}			
			}
		}
		
		new_graph->AddVertex(pseudo_vertex);
	}
	
}

bool has_back_edge (Vertex* now, Vertex* target, Vertex* root){
	if (now == root)
		return false;
	Vertex* parant = now->GetParant();
	now=parant;
	while (now!=root) {
		parant = now->GetParant();
		if (target==parant)
			return true;
		now = parant;
	}
	return false;
}

void trace_back_setup (Vertex* now, Vertex* root) {
	while (now!=root) {
		Vertex* parant = now->GetParant();
		if (parant->low_ > now->low_) 
			parant->low_ = now->low_;
		now = parant;
	}
}

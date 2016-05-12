#ifndef FUNCTION
#define FUNCTION

#include "graph.hpp"
#include "vertex.hpp"

void get_shrink_graph (Vertex* root, Graph* in_graph, Graph* new_graph);
void trace_back_setup (Vertex* now, Vertex* root);
bool has_back_edge (Vertex* now, Vertex* target,Vertex* root);

#endif

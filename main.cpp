#include "vertex.hpp"
#include "edge.hpp"
#include "resident.hpp"
#include "source.hpp"
#include "wire.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

template <typename Key, typename Value>
Value* FindOrInitialize(map<Key, Value*>& objects, Key key, Value* initialized_object);

Vertex* FindOrInitializeVertexWithName(map<string, Vertex*>& vertices, string name);

int main(int argc, char* argv[])
{
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " input.net" << endl;
  }

  ifstream input(argv[1]);

  map<string, Vertex*> all_vertices;
  map<string, Edge*> all_edges;

  // Since all the power sources and residents in ckt.net have no edge connected to its neighbor
  // vertex, we create pseudo wires to connect them.
  const string pseudo_wire_name_prefix("PW");
  int counter = 0;

  string line_string;
  while (getline(input, line_string)) {
    stringstream line_ss(line_string);

    string type;
    line_ss >> type;

    string name;
    line_ss >> name;
    if (name.find('@') == string::npos) {
      string tmp;
      line_ss >> tmp;
      name += " " + tmp;
    }

    if (type == "resid" || type == "small" || type == "large" || type == "source") {
      string neighbor_vertex_name;
      line_ss >> neighbor_vertex_name;
      Vertex* neighbor_vertex = FindOrInitializeVertexWithName(all_vertices, neighbor_vertex_name);
      all_vertices.insert(make_pair(neighbor_vertex_name, neighbor_vertex));

      string pseudo_wire_name = pseudo_wire_name_prefix + to_string(counter++) + '@' + neighbor_vertex->GetRaw()->GetPhase();
      Edge* pseudo_wire_edge;
      pseudo_wire_edge = new Edge(new Wire(pseudo_wire_name));
      all_edges.insert(make_pair(pseudo_wire_name, pseudo_wire_edge));

      double power;
      line_ss >> power;

      Vertex* vertex;
      if (type == "source") {
        Source* source = new Source(name, power);

        vertex = new Vertex(source);
        vertex->AddEdge(pseudo_wire_edge);
      } else {
        Resident* resident = new Resident(name, power);

        vertex = new Vertex(resident);
        vertex->AddEdge(pseudo_wire_edge);
      }
      all_vertices.insert(make_pair(name, vertex));

      neighbor_vertex->AddEdge(pseudo_wire_edge);
      pseudo_wire_edge->AddVertex(neighbor_vertex);
      pseudo_wire_edge->AddVertex(vertex);
    } else {
      string vertex_a_name;
      line_ss >> vertex_a_name;
      Vertex* vertex_a = FindOrInitializeVertexWithName(all_vertices, vertex_a_name);
      all_vertices.insert(make_pair(vertex_a_name, vertex_a));

      string vertex_b_name;
      line_ss >> vertex_b_name;
      Vertex* vertex_b = FindOrInitializeVertexWithName(all_vertices, vertex_b_name);
      all_vertices.insert(make_pair(vertex_b_name, vertex_b));

      Edge* edge;
      if (type == "wire") {
        double resistence;
        line_ss >> resistence;

        double current_limit;
        line_ss >> current_limit >> current_limit;

        Wire* wire = new Wire(name, resistence, current_limit);

        edge = new Edge(wire);
      } else if (type == "switch") {
      } else {
      }
      all_edges.insert(make_pair(name, edge));

      /* edge->AddVertex(vertex_a); */
      /* edge->AddVertex(vertex_b); */
      /* vertex_a->AddEdge(edge); */
      /* vertex_b->AddEdge(edge); */
    }
  }

  /* for (auto& vertex : all_vertices) { */
  /*   vertex.second->Print(); */
  /* } */

  return 0;
}

// This function is **useless**.
// Given a map with key type K and value type V, find if there is a object
// whose key is key. If found, return the found object, otherwise, return the
// initialized object.
template <typename Key, typename Value>
Value* FindOrInitialize(map<Key, Value*>& objects, Key key, Value* initialized_object)
{
  if (objects.find(key) != objects.end()) {
    delete initialized_object;
    return objects.find(key)->second;
  }
  return initialized_object;
}

Vertex* FindOrInitializeVertexWithName(map<string, Vertex*>& vertices, string name)
{
  if (vertices.find(name) != vertices.end()) {
    return vertices.find(name)->second;
  }
  Vertex* vertex = new Vertex(new Node(name));
  return vertex;
}

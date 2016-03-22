#include "vertex.hpp"
#include "edge.hpp"
#include "resident.hpp"
#include "source.hpp"
#include "wire.hpp"
#include "switch.hpp"

#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

Vertex* FindOrInitializeVertexWithName(map<string, Vertex*>& vertices, string name);

int main(int argc, char* argv[])
{
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " input.net" << endl;
  }

  ifstream input(argv[1]);

  map<string, Vertex*> all_vertices;
  map<string, Edge*> all_edges;

  map<string, Source*> all_sources;
  vector<pair<Resident*, string> > resident_source_connections;

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

      string pseudo_wire_name = pseudo_wire_name_prefix + to_string(counter++) + "@" + neighbor_vertex->GetRaw()->GetPhase();
      Edge* pseudo_wire_edge;
      pseudo_wire_edge = new Edge(new Wire(pseudo_wire_name));
      all_edges.insert(make_pair(pseudo_wire_name, pseudo_wire_edge));

      double power;
      line_ss >> power;

      Vertex* vertex;
      if (type == "source") {
        Source* source = new Source(name, power);

        all_sources.insert(make_pair(name, source));

        vertex = new Vertex(source);
        vertex->AddEdge(pseudo_wire_edge);
      } else {
        string source_name;
        line_ss >> source_name;
        if (source_name.find(')') == string::npos) {
          string tmp;
          line_ss >> tmp;

          source_name += " " + tmp;
        }
        source_name += string("@") + neighbor_vertex->GetRaw()->GetPhase();

        Resident* resident = new Resident(name, power);

        resident_source_connections.push_back(make_pair(resident, source_name));

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

      string vertex_b_name;
      line_ss >> vertex_b_name;
      Vertex* vertex_b = FindOrInitializeVertexWithName(all_vertices, vertex_b_name);

      Edge* edge;
      if (type == "wire") {
        double resistence;
        line_ss >> resistence;

        double current_limit;
        line_ss >> current_limit >> current_limit;

        Wire* wire = new Wire(name, resistence, current_limit);

        edge = new Edge(wire);
      } else if (type == "switch") {
        string tmp;
        line_ss >> tmp;

        bool is_on = (tmp == "on") ? true : false;
        Switch* s = new Switch(name, is_on);

        edge = new Edge(s);
      } else {
        double resistence = 0;
        double current_limit = INT_MAX;

        Wire* wire = new Wire(name, resistence, current_limit);

        edge = new Edge(wire);
      }
      all_edges.insert(make_pair(name, edge));

      edge->AddVertex(vertex_a);
      edge->AddVertex(vertex_b);
      vertex_a->AddEdge(edge);
      vertex_b->AddEdge(edge);
    }
  }

  for (auto pair : resident_source_connections) {
    Source* source = all_sources.find(pair.second)->second;

    pair.first->SetSource(source);
    source->AddLoadingResident(pair.first);
  }

  for (auto& vertex : all_vertices) {
    vertex.second->GetRaw()->Print();
    cout << endl;
  }
  for (auto& edge : all_edges) {
    edge.second->GetRaw()->Print();
    cout << endl;
  }

  return 0;
}

// Find vertex with the given name, and return it if found in the given map,
// otherwise, initialize a new vertex and insert it into the given map.
Vertex* FindOrInitializeVertexWithName(map<string, Vertex*>& vertices, string name)
{
  if (vertices.find(name) != vertices.end()) {
    return vertices.find(name)->second;
  }
  Vertex* vertex = new Vertex(new Node(name));
  vertices.insert(make_pair(name, vertex));
  return vertex;
}

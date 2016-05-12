#include "grid.hpp"

#include "source_vertex.hpp"
#include "resident_vertex.hpp"
#include "switch_edge.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

Grid::Grid(SmartGrid* smart_grid, char phase) : smart_grid_(smart_grid), phase_(phase), graph_(new Graph)
{
}

Grid::~Grid()
{
  delete graph_;
  graph_ = nullptr;
}

void Grid::Print() const
{
  cout << "Grid: " << endl;
  cout << "  phase: " << phase_ << endl;
  graph_->Print();
}

void Grid::ParseGrid(ifstream& input)
{
  const string pseudo_wire_prefix("PW");
  int pseudo_wire_count = 0;

  string line_str;
  while (getline(input, line_str)) {
    if (line_str.empty() || line_str[0] == '/') {
      continue;
    }

    stringstream line_ss(line_str);

    string type;
    line_ss >> type;

    string name;
    line_ss >> name;

    Equipment* equipment = smart_grid_->GetEquipment(name);
    assert(equipment != nullptr);

    if (type == "vertex") {
      Node* node = dynamic_cast<Node*>(equipment);

      Vertex* vertex;
      switch (node->GetType()) {
        case Node::Type::NODE:
          vertex = new Vertex(node);

          break;
        case Node::Type::SOURCE:
          {
            vertex = new SourceVertex(dynamic_cast<Source*>(node));

            string neighbor_vertex_name;
            line_ss >> neighbor_vertex_name;

            Vertex* neighbor_vertex = graph_->GetVertex(neighbor_vertex_name);
            assert(neighbor_vertex != nullptr);

            Wire* pseudo_wire = new Wire(pseudo_wire_prefix + to_string(pseudo_wire_count++));
            smart_grid_->AddEquipment(pseudo_wire);

            Edge* pseudo_wire_edge = new Edge(pseudo_wire);
            graph_->AddEdge(pseudo_wire_edge);

            vertex->AddIncidentEdge(pseudo_wire_edge);
            neighbor_vertex->AddIncidentEdge(pseudo_wire_edge);
            pseudo_wire_edge->AddIncidentVertex(vertex);
            pseudo_wire_edge->AddIncidentVertex(neighbor_vertex);

            break;
          }
        case Node::Type::RESIDENT:
          {
            vertex = new ResidentVertex(dynamic_cast<Resident*>(node));

            string neighbor_vertex_name;
            line_ss >> neighbor_vertex_name;

            Vertex* neighbor_vertex = graph_->GetVertex(neighbor_vertex_name);
            assert(neighbor_vertex != nullptr);

            Wire* pseudo_wire = new Wire(pseudo_wire_prefix + to_string(pseudo_wire_count++));
            smart_grid_->AddEquipment(pseudo_wire);

            Edge* pseudo_wire_edge = new Edge(pseudo_wire);
            graph_->AddEdge(pseudo_wire_edge);

            vertex->AddIncidentEdge(pseudo_wire_edge);
            neighbor_vertex->AddIncidentEdge(pseudo_wire_edge);
            pseudo_wire_edge->AddIncidentVertex(vertex);
            pseudo_wire_edge->AddIncidentVertex(neighbor_vertex);

            string source_vertex_name;
            line_ss >> source_vertex_name;

            assert(graph_->GetVertex(source_vertex_name) != nullptr);
            SourceVertex* source_vertex = dynamic_cast<SourceVertex*>(graph_->GetVertex(source_vertex_name));

            ResidentVertex* resident_vertex = dynamic_cast<ResidentVertex*>(vertex);
            resident_vertex->SetSource(source_vertex);

            break;
          }
      }

      graph_->AddVertex(vertex);
    } else if (type == "edge") {
      Wire* wire = dynamic_cast<Wire*>(equipment);

      string vertex_a_name;
      line_ss >> vertex_a_name;

      Vertex* vertex_a = graph_->GetVertex(vertex_a_name);
      assert(vertex_a != nullptr);

      string vertex_b_name;
      line_ss >> vertex_b_name;

      Vertex* vertex_b = graph_->GetVertex(vertex_b_name);
      assert(vertex_b != nullptr);

      Edge* edge;
      switch (wire->GetType()) {
        case Wire::Type::WIRE:
          edge = new Edge(wire);

          break;
        case Wire::Type::SWITCH:
          edge = new SwitchEdge(dynamic_cast<Switch*>(wire));

          break;
	
      }

      vertex_a->AddIncidentEdge(edge);
      vertex_b->AddIncidentEdge(edge);
      edge->AddIncidentVertex(vertex_a);
      edge->AddIncidentVertex(vertex_b);

      graph_->AddEdge(edge);
    } else {
      continue;
    }
  }
}

char Grid::GetPhase() const
{
  return phase_;
}

Graph* Grid::GetGraph() const{
  return graph_;
}

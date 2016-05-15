#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "vertex.hpp"
#include "edge.hpp"

#include <map>
#include <vector>
class Graph
{
  public:
    Graph();
    ~Graph();

    void Print() const;

    Vertex* GetVertex(std::string name) const;
    Edge* GetEdge(std::string name) const;
    void FlushVertexMark();
    void FlushVisit();
    int GetVertexNum();
    void AddVertex(Vertex* vertex);
    void AddEdge(Edge* edge);
    bool GetSource (Vertex* &source);
    Vertex* GetSource(int);
    int GetSourceNum();
    void SetVertexArtic();

  private:
    //bool should_delete_;
    std::vector<Vertex*> sources_;
    std::map<std::string, Vertex*> vertices_;
    std::map<std::string, Edge*> edges_;

};

#endif

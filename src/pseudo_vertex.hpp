#ifndef PSEUDO_VERTEX_HPP
#define PSEUDO_VERTEX_HPP

#include "graph.hpp"

#include <map>

class Graph;

class PseudoVertex : public Vertex
{
  public:
    PseudoVertex(Node* raw);
    virtual ~PseudoVertex();

    virtual void Print() const;

    void MergeDescendants(Vertex* root);
    void MergeBySwitches(Vertex* root);

    double GetConsumingPower() const;

    Graph* GetGraph() const;

    Vertex* GetBoundaryVertex(Edge* edge) const;
    std::vector<Vertex*> GetBoundaryVertices() const;

    void AddBoundaryVertex(Edge* edge, Vertex* vertex);



  private:
    double consuming_power_;
    

    Graph* graph_;
    
    // Since the vertex on an edge will be replaced by a pseudo vertex when the
    // edge is connecting to a pseudo vertex, the original vertex must be
    // recorded.
    //
    // For example, when connecting an edge E to a pseudo vertex PV:
    //
    //     E                            E'
    //     |  |---- PV ----|   \        |
    // V -----| V ----- V  |   =\   V ----- PV
    //        | |       |  |   ==\
    //        | |       V  |   ==/
    //        | V          |   =/
    //        |------------|   /
    //
    // It will construct a new edge E' connecting the V and the PV, therefore,
    // which vertex E' actually connects to is unknown.
    //
    // For convenience, the original vertices is indexed by the edge E'.
    std::map<Edge*, Vertex*> boundary_vertices_;
    
    

};

#endif

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "node.hpp"
#include "edge.hpp"

#include <vector>

class Edge;

class Vertex
{
  public:
    enum class Type
    {
      VERTEX,
      SOURCE,
      RESIDENT,
      PSEUDO
    };

    Vertex(Node* raw, Type type = Type::VERTEX);
    virtual ~Vertex() = default;

    virtual void Print() const;

    Node* GetRaw() const;
    Type GetType() const;
    void AddIncidentEdge(Edge* edge);
    Edge* GetIncidentEdge(int);
    int GetIncidentEdgeNum();
    double GetVoltage ();
    bool GetVisit();
    void SetVisit(bool);
    Vertex* GetParant();
    void SetParant (Vertex*);
    void AddChild (Vertex*);
    Vertex* GetChild (int);
    int GetChildNum ();
    bool GetIsArtic();
    void SetIsArtic(bool);
    
    int index_num_, low_;

  private:
    bool visit_;
    bool is_artic_;
    std::vector<Edge*> incident_edges_;

    Vertex* parant_;
    std::vector<Vertex*> children_;
    

    Node* raw_;
    Type type_;
    double voltage_;

};

#endif

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "node.hpp"
#include "edge.hpp"

#include <vector>

class Grid;
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

    Grid* GetGrid() const;
    Node* GetRaw() const;
    Type GetType() const;
    double GetVoltage() const;

    int GetIncidentEdgesNum() const;
    Edge* GetIncidentEdge(int idx) const;

    bool GetIsVisited() const;
    Vertex* GetParent() const;
    int GetChildrenNum() const;
    Vertex* GetChild(int idx) const;
    int GetDepth() const;
    int GetLow() const;
    int GetIsArticulate() const;

    void SetGrid(Grid* grid);

    void SetIsVisted(bool is_visited = true);
    void SetParent(Vertex* parent);
    void SetDepth(int depth);
    void SetLow(int low);
    void SetIsArticulate(bool is_articulate);

    void AddIncidentEdge(Edge* incident_edge);
    void AddChild(Vertex* child);
    void ResetMarks();

  private:
    Grid* grid_;

    Node* raw_;
    Type type_;
    double voltage_;

    std::vector<Edge*> incident_edges_;

    Vertex* parent_;
    std::vector<Vertex*> children_;
    int depth_;

    int low_;
    bool is_articulate_;

};

#endif

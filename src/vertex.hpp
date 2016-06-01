#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "node.hpp"
#include "edge.hpp"
#include <map>
#include <vector>
#include <algorithm>

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
    int GetSourceDistance (Vertex*);
    std::string GetAssignSource();
    int GetDistanceDiff();
    Vertex* GetSourcePriority(int);
    int GetPriorityNum();
    double GetVoltage();

    void SetGrid(Grid* grid);

    void SetIncidentEdge(int idx, Edge* incident_edge);

    void SetIsVisted(bool is_visited = true);
    void SetParent(Vertex* parent);
    void SetDepth(int depth);
    void SetLow(int low);
    void SetIsArticulate(bool is_articulate);
    void SetSourceDistance (Vertex*, int);
    void SetAssignSource(std::string);
    void SetVoltage(double);

    void AddIncidentEdge(Edge* incident_edge);
    void AddChild(Vertex* child);
    void ResetMarks();
    void CountDistanceDiff ();
    void SetIsSource(bool);
    bool GetIsSource();

    void SetParentEdge(Edge*);
    Edge* GetParentEdge();

  private:
    Grid* grid_;

    Node* raw_;
    Type type_;
    double voltage_;

    std::vector<Edge*> incident_edges_;

    Vertex* parent_;
    Edge* parent_edge_;
    std::vector<Vertex*> children_;
    int depth_;

    int low_;
    bool is_articulate_;
    std::string assign_source_;
    std::map<Vertex*, int> source_distance_;
    std::vector<std::pair<Vertex*, int>> source_priority_;
    int distance_diff_;
    bool is_source_;

};

#endif

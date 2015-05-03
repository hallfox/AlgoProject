#include "Vertex.h"

Vertex::Vertex()
{
    val = 0;
}

Vertex::Vertex(int v)
{
    val = v;
}

Vertex::Vertex(const Vertex& v)
{
    edges = std::list<Edge>(v.edges);
    val = v.val;
}

void Vertex::addEdge(Vertex* v, double w)
{
    edges.push_back(Edge(this->val, v->val, w));
}

void Vertex::addEdge(Edge e)
{
    edges.push_back(e);
}

void Vertex::addInEdge(Vertex *v, double w) {
  edges.push_back(Edge(v->val, this->val, w));
}

void Vertex::addInEdge(Edge e) {
  inEdges.push_back(e);
}

int Vertex::getValue()
{
    return val;
}

const std::list<Edge>& Vertex::getEdges() {
  return edges;
}

const std::list<Edge>& Vertex::getInEdges() {
  return inEdges;
}

std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
    // Vertex (val): <Edges(val, weight)>
    os << "Vertex (" << v.val << "): ";

    for (typename std::list<Edge>::const_iterator iter = v.edges.begin();
        iter != v.edges.end(); iter++)
    {
        os << "Edge<" << iter->end << ", " << iter->weight << "> ";
    }

    return os;
}

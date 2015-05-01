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
    edges.push_back((Edge) {start: val, end: v.val, weight: });
}

void Vertex::addEdge(Edge e)
{
    edges.push_back(e);
}

int Vertex::getValue()
{
    return val;
}

std::list<Edge> Vertex::getEdges() {
  return edges;
}

std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
    // Vertex (val): <Edges(val, weight)>
    os << "Vertex (" << v.val << "): ";

    for (typename std::list<Edge>::const_iterator iter = v.edges.begin();
        iter != v.edges.end(); iter++)
    {
        os << "Edge<" << iter->first->getValue() << ", " << iter->second << "> ";
    }

    return os;
}

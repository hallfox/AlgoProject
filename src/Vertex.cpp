#include "Vertex.h"

Vertex::Vertex()
{
    val = "";
}

Vertex::Vertex(std::string ele)
{
    val = ele;
}

Vertex::Vertex(const Vertex& v)
{
    edges = std::list<Edge>(v.edges);
    val = std::string(v.val);
}

void Vertex::addEdge(Vertex* v, int weight)
{
    edges.push_back(std::make_pair(v, weight));
}

void Vertex::addEdge(Edge e)
{
    edges.push_back(e);
}

std::string Vertex::getValue()
{
    return val;
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

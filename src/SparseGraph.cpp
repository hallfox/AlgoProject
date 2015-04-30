#include <sstream>
#include <fstream>

#include "SparseGraph.h"

SparseGraph::SparseGraph() 
{
    verts = std::vector<Vertex*>();
}

SparseGraph::SparseGraph(std::ifstream& file)
{
    // READ FORMAT:
    // num verts
    // vert edge weight
    // ...
    int n;

    file >> n;
    verts = std::vector<Vertex*>(n, nullptr);

    int from, to;
    double weight;
    while(true)
    {
        file >> from;
        if (from == -1) break;
        file >> to;
        file >> weight;

        // get a hold of the vertex
        Vertex *v = find(from);
        Vertex *e = find(to);

        if (v == nullptr)
        {
            v = new Vertex(from);
            verts[from] = v;
        }
        if (e == nullptr)
        {
            e = new Vertex(to);
            verts[to] = e;
        }

        v->addEdge(e, weight);

        std::string edgeName, weight;
    }
}

SparseGraph::~SparseGraph()
{
    clear();
}

void SparseGraph::insert(Vertex* v)
{
    verts.push_back(v);
}

void SparseGraph::insert(int val)
{
    insert(new Vertex(val));
}

void SparseGraph::clear()
{
    for (typename std::vector<Vertex*>::iterator iter = verts.begin();
            iter != verts.end(); iter++)
    {
        delete (*iter);
        *iter = nullptr;
    }
}

Vertex* SparseGraph::find(int val)
{
    return verts[val];
}

const std::vector<Vertex*>& SparseGraph::getVertices()
{
    return verts;
}

std::ostream& operator<<(std::ostream& os, const SparseGraph& g)
{
    for (typename std::vector<Vertex*>::const_iterator iter = g.verts.begin();
            iter != g.verts.end(); iter++)
    {
        if (*iter != nullptr)
            os << **iter << "\n";
    }

    return os;
}


#include <sstream>

#include "SparseGraph.h"

SparseGraph::SparseGraph() 
{
    verts = std::vector<Vertex*>();
}

SparseGraph::SparseGraph(int n)
{
    verts = std::vector<Vertex*>(n);
}

SparseGraph::~SparseGraph()
{
    clear();
}

void SparseGraph::insert(Vertex* v)
{
    verts.push_back(v);
}

void SparseGraph::insert(const std::string& val)
{
    insert(new Vertex(val));
}

void SparseGraph::clear()
{
    for (typename std::vector<Vertex*>::iterator iter = verts.begin();
            iter != verts.end(); iter++)
    {
        delete *iter;
    }
}

Vertex* SparseGraph::find(const std::string& val)
{
    for (typename std::vector<Vertex*>::const_iterator iter = verts.begin();
            iter != verts.end(); iter++)
    {
        if ((*iter)->getValue() == val)
        {
            return *iter;
        }
    }

    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const SparseGraph& g)
{
    for (typename std::vector<Vertex*>::const_iterator iter = g.verts.begin();
            iter != g.verts.end(); iter++)
    {
        os << **iter << "\n";
    }

    return os;
}

SparseGraph* ReadSparseGraph(const std::string& filename)
{
    // READ FORMAT:
    // num verts
    // val edge weight
    // ...
    
    int n;
    std::cin >> n;

    SparseGraph *g = new SparseGraph(n);

    for (int i = 0; i < n; i++)
    {
        std::string s;
        std::getline(std::cin, s);
        std::stringstream sstm(s);

        std::string vertName;
        sstm >> vertName;

        // get a hold of the vertex
        Vertex *v = g->find(vertName);

        if (v == nullptr)
        {
            v = new Vertex(vertName);
            g->insert(v);
        }

        std::string edgeName, weight;
        while ((sstm >> edgeName) && (sstm >> weight))
        {
            Vertex *edge = g->find(edgeName);

            if (edge == nullptr)
            {
                edge = new Vertex(edgeName);
                g->insert(edge);
            }

            int w = std::stoi(weight);

            v->addEdge(edge, w);
        }
    }

    return g;
}

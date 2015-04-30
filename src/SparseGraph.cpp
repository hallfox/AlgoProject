#include <sstream>
#include <fstream>

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
        delete (*iter);
        *iter = nullptr;
    }
}

Vertex* SparseGraph::find(const std::string& val)
{
    for (typename std::vector<Vertex*>::const_iterator iter = verts.begin();
            iter != verts.end(); iter++)
    {
        //std::cout << *iter << "\n";
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
    
    std::ifstream file(filename);
    
    std::string size;
    int n;
    std::getline(file, size);
    n = std::stoi(size);

    SparseGraph *g = new SparseGraph();

    for (int i = 0; i < n; i++)
    {
        std::string s;
        std::getline(file, s);
        std::stringstream sstm(s);

        std::string vertName;
        sstm >> vertName;

        //std::cout << "Reading in: " << vertName << "\n";

        // get a hold of the vertex
        Vertex *v = g->find(vertName);

        if (v == nullptr)
        {
            v = new Vertex(vertName);
            g->insert(v);
            //std::cout << "Added vertex: " << vertName << "\n";
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

    file.close();

    return g;
}

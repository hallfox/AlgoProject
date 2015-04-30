#include <sstream>

#include "SparseGraph.h"

template <class T>
SparseGraph<T>::SparseGraph() 
{
    verts = std::vector<Vertex<T>* >();
}

template <class T>
SparseGraph<T>::SparseGraph(int n)
{
    verts = std::vector<Vertex<T>* >(n);
}

template <class T>
SparseGraph<T>::~SparseGraph()
{
    clear();
}

template <class T>
void SparseGraph<T>::insert(Vertex<T>* v)
{
    verts.push_back(v);
}

template <class T>
void SparseGraph<T>::insert(const T& val)
{
    insert(new Vertex<T>(val));
}

template <class T>
void SparseGraph<T>::clear()
{
    for (typename std::vector<Vertex<T>* >::iterator iter = verts.begin();
            iter != verts.end(); iter++)
    {
        delete *iter;
    }
}

template <class T>
Vertex<T>* SparseGraph<T>::find(const T& val)
{
    for (typename std::vector<Vertex<T>* >::const_iterator iter = verts.begin();
            iter != verts.end(); iter++)
    {
        if ((*iter)->getValue() == val)
        {
            return *iter;
        }
    }

    return nullptr;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const SparseGraph<T>& g)
{
    for (typename std::vector<Vertex<T> >::const_iterator iter = g.verts.begin();
            iter != g.verts.end(); iter++)
    {
        os << **iter << "\n";
    }

    return os;
}

SparseGraph<std::string>* ReadSparseGraph(const std::string& filename)
{
    // READ FORMAT:
    // num verts
    // val edge weight
    // ...
    
    int n;
    std::cin >> n;

    SparseGraph<std::string> *g = new SparseGraph<std::string>(n);

    for (int i = 0; i < n; i++)
    {
        std::string s;
        std::getline(std::cin, s);
        std::stringstream sstm(s);

        std::string vertName;
        sstm >> vertName;

        // get a hold of the vertex
        Vertex<std::string> *v = g->find(vertName);

        if (v == nullptr)
        {
            v = new Vertex<std::string>(vertName);
            g->insert(v);
        }

        std::string edgeName, weight;
        while ((sstm >> edgeName) && (sstm >> weight))
        {
            Vertex<std::string> *edge = g->find(edgeName);

            if (edge == nullptr)
            {
                edge = new Vertex<std::string>(edgeName);
                g->insert(edge);
            }

            int w = std::stoi(weight);

            v->addEdge(edge, w);
        }
    }

    return g;
}

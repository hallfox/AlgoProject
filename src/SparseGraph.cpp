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
void SparseGraph<T>::insert(const Vertex<T>* v)
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
std::ostream& operator<<(std::ostream& os, const SparseGraph<T>& g)
{
    for (typename std::vector<Vertex<T> >::const_iterator iter = g.verts.begin();
            iter != g.verts.end(); iter++)
    {
        os << **iter << "\n";
    }

    return os;
}

SparseGraph<std::string>* readSparseGraph(const std::string& filename)
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
    }

    return g;
}

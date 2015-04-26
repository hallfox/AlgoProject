#include "SparseGraph.h"

template <class T>
SparseGraph<T>::SparseGraph() 
{
    verts = std::vector<Vertex<T>* >();
}

template <class T>
SparseGraph<T>::~SparseGraph()
{
    for (typename std::vector<Vertex<T>* >::const_iterator iter = verts.begin();
            iter != verts.end(); iter++)
    {
        delete (*iter);
    }
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

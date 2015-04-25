#include "SparseGraph.h"

template <class T>
SparseGraph<T>::SparseGraph() {};

template <class T>
void SparseGraph<T>::insert(Vertex<T> v)
{
    verts.push_back(v);
}

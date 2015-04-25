#include "Vertex.h"

template <class T>
Vertex<T>::Vertex(T ele)
{
    val = ele;
}

template <class T>
void Vertex<T>::addEdge(Edge e)
{
    edges.push_back(e);
}

#include "Vertex.h"

template <class T>
Vertex<T>::Vertex()
{
    val = T();
}

template <class T>
Vertex<T>::Vertex(T ele)
{
    val = ele;
}

template <class T>
Vertex<T>::Vertex(const Vertex<T>& v)
{
    edges = std::list<Edge<T> >(v.edges);
    val = T(v.val);
}

template <class T>
void Vertex<T>::addEdge(Vertex<T>* v, int weight)
{
    edges.push_back(std::make_pair(v, weight));
}

template <class T>
void Vertex<T>::addEdge(Edge<T> e)
{
    edges.push_back(e);
}

template <class T>
T Vertex<T>::getValue()
{
    return val;
}

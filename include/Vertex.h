#ifndef __VERTEX_H
#define __VERTEX_H

#include <list>
#include <utility>

template <class T>
class Vertex
{
    // an edge, which points to a vertex and has a weight
    typedef std::pair<Vertex<T>*, int> Edge;

    public:
        Vertex(T);
        void addEdge(Edge);
    private:
        std::list<Edge> edges;
        T val;
};

#endif

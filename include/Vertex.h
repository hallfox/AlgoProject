#ifndef __VERTEX_H
#define __VERTEX_H

#include <list>
#include <utility>
#include <iostream>

template <class T> class Vertex;

// an edge, which points to a vertex and has a weight
template <class T>
using Edge = std::pair<Vertex<T>*, int>;

template <class T>
class Vertex
{
    public:
        Vertex();
        Vertex(T);
        Vertex(const Vertex<T>&);
        void addEdge(Vertex<T>*, int);
        void addEdge(Edge<T>);
        T getValue();

        // inline because templating
        friend std::ostream& operator<<(std::ostream& os, const Vertex<T>& v)
        {
            // Vertex (val): <Edges(val, weight)>
            os << "Vertex (" << v.val << "): ";

            for (typename std::list<Edge<T> >::const_iterator iter = v.edges.begin();
                iter != v.edges.end(); iter++)
            {
                os << "Edge<" << iter->first << ", " << iter->second << "> ";
            }

            return os;
        }
    private:
        std::list<Edge<T> > edges;
        T val;
};

#endif

#ifndef __VERTEX_H
#define __VERTEX_H

#include <list>
#include <utility>
#include <iostream>

class Vertex;

// an edge, which points to a vertex and has a weight
typedef std::pair<Vertex*, double> Edge;

class Vertex
{
    public:
        Vertex();
        Vertex(int);
        Vertex(const Vertex&);
        void addEdge(Vertex*, double);
        void addEdge(Edge);
        int getValue();

        friend std::ostream& operator<<(std::ostream&, const Vertex&);
    private:
        std::list<Edge> edges;
        int val;
};

#endif

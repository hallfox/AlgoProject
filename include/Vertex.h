#ifndef __VERTEX_H
#define __VERTEX_H

#include <list>
#include <utility>
#include <iostream>

#include "Edge.h"

class Vertex
{
    public:
        Vertex();
        Vertex(int);
        Vertex(const Vertex&);
        void addEdge(Vertex*, double);
        void addEdge(Edge);
        int getValue();
        const std::list<Edge>& getEdges();
        friend std::ostream& operator<<(std::ostream&, const Vertex&);
    private:
        std::list<Edge> edges;
        int val;
};

#endif

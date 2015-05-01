#ifndef __VERTEX_H
#define __VERTEX_H

#include <list>
#include <utility>
#include <iostream>

// an edge, which points to a vertex and has a weight

class Vertex
{
    typedef std::pair<int, double> Edge;
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
        //typedef std::pair<Vertex*, double> Edge;
        std::list<Edge> edges;
        int val;
};

#endif

#ifndef __VERTEX_H
#define __VERTEX_H

#include <list>
#include <utility>
#include <iostream>

class Vertex;

// an edge, which points to a vertex and has a weight
typedef std::pair<Vertex*, int> Edge;

class Vertex
{
    public:
        Vertex();
        Vertex(std::string);
        Vertex(const Vertex&);
        void addEdge(Vertex*, int);
        void addEdge(Edge);
        std::string getValue();

        friend std::ostream& operator<<(std::ostream&, const Vertex&);
    private:
        std::list<Edge> edges;
        std::string val;
};

#endif

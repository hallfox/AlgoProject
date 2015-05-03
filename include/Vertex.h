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
	void addInEdge(Vertex *, double);
	void addInEdge(Edge);
        const std::list<Edge>& getEdges();
	const std::list<Edge>& getInEdges();
        friend std::ostream& operator<<(std::ostream&, const Vertex&);
    private:
        std::list<Edge> edges;
	std::list<Edge> inEdges;
        int val;
};

#endif

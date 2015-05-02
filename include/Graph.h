#ifndef __GRAPH_H
#define __GRAPH_H

#include <list>

#include "Edge.h"

class Graph
{
    public:
        virtual int getVertSize() = 0;
        virtual const std::list<Edge> getEdges(int) = 0;
};

#endif

#ifndef __GRAPH_H
#define __GRAPH_H

template <class T>
class Graph
{
    public:
        virtual void insert(const T&) = 0;
        virtual void getVertices() = 0;
        
};

#endif

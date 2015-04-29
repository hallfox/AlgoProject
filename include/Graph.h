#ifndef __GRAPH_H
#define __GRAPH_H

// super class of Sparse and Dense Graphs
template <class T>
class Graph
{
    public:
        virtual void insert(const T&) = 0;
};

#endif

#ifndef __SPARSE_GRAPH_H
#define __SPARSE_GRAPH_H

#include <vector>

#include "Vertex.h"

template <class T>
class SparseGraph
{
    public:
        SparseGraph();
        void insert(Vertex<T>);

    private:
        std::vector< Vertex<T> > verts;
};

#endif

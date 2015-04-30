#ifndef __SPARSE_GRAPH_H
#define __SPARSE_GRAPH_H

#include <vector>
#include <iostream>

#include "Vertex.h"

template <class T>
class SparseGraph
{
    public:
        SparseGraph();
        SparseGraph(int);
        ~SparseGraph();
        void insert(Vertex<T>*);
        void insert(const T&);
        Vertex<T>* find(const T& val);

        friend std::ostream& operator<<(std::ostream&, const SparseGraph<T>&);
    private:
        void clear();
        std::vector<Vertex<T>* > verts;
};

SparseGraph<std::string>* ReadSparseGraph(const std::string& filename);

#endif

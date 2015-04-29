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
        void insert(const Vertex<T>*);
        void insert(const T&);

        friend std::ostream& operator<<(std::ostream&, const SparseGraph<T>&);
    private:
        void clear();
        std::vector<Vertex<T>* > verts;
};

SparseGraph<std::string>* readSparseGraph(const std::string& filename);

#endif

OD#ifndef __SPARSE_GRAPH_H
#define __SPARSE_GRAPH_H

#include <vector>
#include <iostream>
#include <fstream>

#include "Vertex.h"

class SparseGraph
{
    public:
        SparseGraph();
        SparseGraph(std::ifstream&);
        ~SparseGraph();
        void insert(Vertex*);
        void insert(int);
        Vertex* find(int);
        const std::vector<Vertex*>& getVertices();

        friend std::ostream& operator<<(std::ostream&, const SparseGraph&);
    private:
        void clear();
        std::vector<Vertex*> verts;
};

#endif

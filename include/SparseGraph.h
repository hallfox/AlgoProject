#ifndef __SPARSE_GRAPH_H
#define __SPARSE_GRAPH_H

#include <vector>
#include <iostream>

#include "Vertex.h"

class SparseGraph
{
    public:
        SparseGraph();
        SparseGraph(int);
        ~SparseGraph();
        void insert(Vertex*);
        void insert(const std::string&);
        Vertex* find(const std::string& val);
        const std::vector<Vertex*>& getVertices();

        friend std::ostream& operator<<(std::ostream&, const SparseGraph&);
    private:
        void clear();
        std::vector<Vertex*> verts;
};

SparseGraph* ReadSparseGraph(const std::string& filename);

#endif

#ifndef __SPARSE_GRAPH_H
#define __SPARSE_GRAPH_H

#include <vector>
#include <iostream>
#include <fstream>

#include "Graph.h"
#include "Vertex.h"

class SparseGraph: public Graph
{
    public:
        SparseGraph();
        SparseGraph(std::ifstream&);
        ~SparseGraph();
        void insert(Vertex*);
        void insert(int);
        Vertex* find(int);
        
        virtual int getVertSize();
        virtual const std::list<Edge> getEdges(int);

        friend std::ostream& operator<<(std::ostream&, const SparseGraph&);
    private:
        void clear();
        std::vector<Vertex*> verts;
};

#endif

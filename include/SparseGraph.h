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
        ~SparseGraph();
        void insert(const Vertex<T>*);
        void insert(const T&);

        // inline because templating
        friend std::ostream& operator<<(std::ostream& os, const SparseGraph<T>& g)
        {
            for (typename std::vector<Vertex<T> >::const_iterator iter = g.verts.begin();
                    iter != g.verts.end(); iter++)
            {
                os << **iter << "\n";
            }

            return os;
        }
    private:
        std::vector<Vertex<T>* > verts;
};

#endif

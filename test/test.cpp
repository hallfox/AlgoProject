#include <iostream>

#include "SparseGraph.h"

void testSparseGraphInsert(SparseGraph<std::string>& sgraph)
{
    Vertex<std::string> *v1 = new Vertex<std::string>("Poughkeepsie");
    Vertex<std::string> *v2 = new Vertex<std::string>("Binghamton");
    
    v1->addEdge(v2, 200);
    v2->addEdge(v1, 250);
    sgraph.insert(v1);
    sgraph.insert(v2);   
    std::cout << sgraph;
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::string flags = argv[1];
        if (flags == "-s")
        {
            SparseGraph<std::string> sgraph;
            testSparseGraphInsert(sgraph);
        }
    }
}

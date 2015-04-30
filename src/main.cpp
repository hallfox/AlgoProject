#include <iostream>
#include "SparseGraph.h"

int dijkstra(Vertex start, Vertex end) {
    return 0;    
}

int aStar(Vertex start, Vertex end) {
    return 0; 
}

int main(int argc, char *argv[])
{
    // just a placeholder for now
    std::cout << "Hello world!" << std::endl;
    SparseGraph *sgraph = ReadSparseGraph("test/SmallGraph.txt");
    std::cout << *sgraph;
    delete sgraph;

    return 0;
}

#include <iostream>

#include "SparseGraph.h"

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::string flags = argv[1];
        if (flags == "-s")
        {
            std::string file = "test/SmallGraph.txt";
            std::cout << "Loading " << file << "...\n";
            SparseGraph* sgraph = ReadSparseGraph(file);
            std::cout << sgraph;
            delete sgraph;
        }
    }
}

#include <iostream>
#include <fstream>
#include "SparseGraph.h"
#include "Graph.h"

int dijkstra(Vertex start, Vertex end) {
  std::list<Edge> edges = start.getEdges();
  return 0;    
}

int aStar(Vertex start, Vertex end) {
  return 0; 
}

int main(int argc, char *argv[])
{
  std::ifstream file("test/TestGraph1.txt");
  SparseGraph sgraph(file);
  file.close();
  
  std::cout << sgraph;
  
  return 0;
}

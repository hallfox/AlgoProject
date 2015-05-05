#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <list>
#include <utility>
#include <cmath>
#include <chrono>

#include "Graph.h"
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "Heuristics.h"

typedef std::pair<int, double> VertexKey;
enum Hdist {H_RAND, H_DIJKSTRA, H_EUCLIDIAN, H_MANHATTAN};

struct minComp {
  bool operator()(const VertexKey &a, const VertexKey &b) const {
    return a.second > b.second;
  }
};

void printPath(const std::vector<int> &path, int dest)
{
  int vert = dest;
  while (path[vert] != -1)
  {
    std::cout << vert << ", ";
    vert = path[vert];
  }
}

int aStar(Graph &graph, int start, int end, int heur) {
  int n = graph.getVertSize();
  // nodes that have been visited
  std::vector<bool> visited(n, false);
  // keeps track of shortest distance
  std::vector<double> fromDistance(n, std::numeric_limits<double>::max()); 
  // keeps track of estimated shortest distance
  std::vector<double> estDistance(n);
  // used to reconstruct where the shortest path came from
  std::vector<int> backPath(n, -1);
  
  // the priority queue
  // A VertexKey is a pair<int, double> where int is the vertex id 
  // and double is the estimated distance
  std::priority_queue<VertexKey, std::vector<VertexKey>, minComp> toVisit;
  toVisit.push(std::make_pair(start, 0.0));
  fromDistance[start] = 0;

  // NOTE: since C++ doesn't support a decrease key op and we simply
  // can't be bothered to write our own pqueue, we take the strategy
  // of 'lazy deletion', meaning that when we update a vertex's estimated
  // distance, we simply insert a new VertexKey with the updated distance
  // and node id; because the new distance will always be smaller than the
  // old key, we will always pop the better distance first, so we will
  // always evaluate the nodes as if we called a decrease key
  // This tradeoff requires that we use extra space, but it preserves time
  // complexity O(logn) and we compensate by ignoring vertices that we've
  // already processed
  while(!toVisit.empty()) 
  {
    // pop the best estimated distance off the pq
    VertexKey key = toVisit.top();
    int currVert = key.first;
    toVisit.pop();

    // check to make sure we haven't processed it already due to our
    // 'lazy deletion' strategy
    if (visited[currVert]) continue;

    // did we find the destination?
    if (currVert == end)
    {
        printPath(backPath, end);
        return fromDistance[end];
    }
    
    // mark processed and iterate over the vertex's neighbors
    visited[currVert] = true;
    //std::cout << "-----Vertex: " << currVert << "\n";
    const std::list<Edge> neighbors = graph.getEdges(currVert);
    for (std::list<Edge>::const_iterator iter = neighbors.begin();
	 iter != neighbors.end(); iter++)
    {
        int vNext = iter->end;
        double dist = iter->weight;
        //std::cout << "Considering: " << vNext << "\n";
	
        // get ready to relax the edge
        int tDist = fromDistance[currVert] + dist;
	
        // check if we should relax
        if (!visited[vNext] || tDist < fromDistance[vNext])
        {
            backPath[vNext] = currVert;
            fromDistance[vNext] = tDist;
            // !IMPORTANT: this uses our approximation to head toward the destination
            // h*() must never overestimate the actual distance, or the algorithm may be wrong 
            int size;
            switch(heur)
            {
                case H_DIJKSTRA:
                    estDistance[vNext] = tDist + hDijkstra();
                    break;
                case H_MANHATTAN:
                    size = floor(sqrt(graph.getVertSize()));
                    estDistance[vNext] = tDist + hManhattan(start, end,
                            size, size);
                    break;
                case H_EUCLIDIAN:
                    size = floor(sqrt(graph.getVertSize()));
                    estDistance[vNext] = tDist + hAStarGrid(start, end,
                            size, size);
                    break;
                case H_RAND:
                    estDistance[vNext] = tDist + hAStarRand();
                    break;
            }
            if (!visited[vNext])
            {
                toVisit.push(std::make_pair(vNext, estDistance[vNext]));
            }
        }
    }
  }
  
  return -1;
}

int main(int argc, char *argv[])
{
  const int FILES = 9;
  std::string testFiles[FILES] = { 
      "test/SmallGrid.txt",
      "test/MedGrid.txt",
      "test/LargeGrid.txt",
      "test/SmallGeo.txt",
      "test/MedGeo.txt",
      "test/LargeGeo.txt",
      "test/SmallTorus.txt",
      "test/MedTorus.txt",
      "test/LargeTorus.txt"
  };

  for (int i = 0; i < FILES; i++)
  {
    std::ifstream file(testFiles[i]);
    SparseGraph sgraph(file);
    file.close();

    DenseGraph dgraph;
    dgraph.readFromFile(testFiles[i]);

    int start = 0, end = 0;
    if (i % 3 == 0) end = 19;
    else if (i % 3 == 1) end = 99;
    else end = 499;
    
    std::cout << "File being tested: " << testFiles[i] << "\n";
    std::cout << "-------------------\n";
    for (int h = H_RAND; h <= H_MANHATTAN; h++)
    {
        switch (h)
        {
            case H_RAND: 
                std::cout << "\t\tRandom Heuristic:\n"; break;
            case H_DIJKSTRA: 
                std::cout << "\t\tDijkstra's Algorithm:\n"; break;
            case H_EUCLIDIAN: 
                std::cout << "\t\tEuclidian Distance:\n"; break;
            case H_MANHATTAN: 
                std::cout << "\t\tManhattanDistance:\n"; break;
            default: 
                std::cout << "Unknown algorithm\n"; continue;
        }
        std::cout << "\t\t== Sparse Graph:\n\t\t>> Path: ";
        //std::cout << sgraph << "\n";

        auto sStartTime = std::chrono::high_resolution_clock::now();
        double sDist = aStar(sgraph, start, end, h);
        auto sEndTime = std::chrono::high_resolution_clock::now();
        auto sparseTime = std::chrono::duration_cast<std::chrono::milliseconds>(sEndTime - sStartTime).count();

        std::cout << "\n\t\t== Distance: " << sDist << "\n";
        std::cout << "\t\t== Time: " << sparseTime << "ms\n";
        std::cout << "\t\t== Dense Graph:\n\t\t==Path: ";


        auto dStartTime = std::chrono::high_resolution_clock::now();
        double dDist = aStar(dgraph, start, end, h);
        auto dEndTime = std::chrono::high_resolution_clock::now();
        auto denseTime = std::chrono::duration_cast<std::chrono::milliseconds>(dEndTime - dStartTime).count();

        std::cout << "\n\t\t== Distance: " << dDist << "\n";
        std::cout << "\t\t== Time: " << denseTime << "ms\n";
    }
  }
  
  return 0;
}

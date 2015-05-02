#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include "SparseGraph.h"
#include "Graph.h"
#include "Heuristics.h"

typedef std::pair<int, double> VertexKey;

struct minComp {
    bool operator()(const VertexKey &a, const VertexKey &b) const {
        return a.second > b.second;
    }
};

void reheap(std::vector<VertexKey> heap)
{
    std::make_heap(heap.begin(), heap.end(), minComp);
}

int aStar(Vertex start, Vertex end) {
  std::vector<bool> visited(n, false); // nodes that have been visited
  // this is used in calculating the estimated, showing how far we've already traveled
  std::vector<int> fromDistance(n, std::numeric_limits<int>::max()); 
  // this is the estimated distance from start to end
  std::vector<int> estDistance(n);
  std::vector<int> backPath(n);

  // the priority queue
  // A VertexKey is a pair<int, double> where int is the vertex id 
  // and double is the estimated distance
  std::priority_queue<VertexKey, minComp> toVisit;
  while(!toVisit.empty()) 
  {
    // pop and relax
    VertexKey key = toVisit.top();
    int currVert = key.first;
    double currDist = key.second;
    toVisit.pop();

    if (visited[currVert]) continue;
    if (currVert == end)
    {
        return path();
    }

    visited[currVert] = true;
    std::vector<Edge> neighbors = graph.find(currVert)->getEdges();
    for (std::vector<Edge>::const_iterator iter = neighbors.begin();
            iter != neighbors.end(); iter++)
    {
        int vNext = iter->end;
        double dist = iter->weight;
        int tDist = fromDistance[currVert] + dist;

        if (!visited[vNext] || tDist < fromDistance[*iter])
        {
            backPath[vNext] = currVect;
            fromDistance[vNext] = tDist;
            estDistance[vNext] = tDist + hDist(vNext, end);
            if (!visited[vNext])
            {
                toVisit.push(std::make_pair(vNext, estDistance[vNext]));
            }
        }
    }
  }

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

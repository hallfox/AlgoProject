#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <list>
#include <utility>

#include "Graph.h"
#include "SparseGraph.h"
#include "Heuristics.h"

typedef std::pair<int, double> VertexKey;

struct minComp {
  bool operator()(const VertexKey &a, const VertexKey &b) const {
    return a.second > b.second;
  }
};

int aStar(Graph &graph, int start, int end) {
  int n = graph.getVertSize();
  // nodes that have been visited
  std::vector<bool> visited(n, false);
  // keeps track of shortest distance
  std::vector<int> fromDistance(n, std::numeric_limits<int>::max()); 
  // keeps track of estimated shortest distance
  std::vector<int> estDistance(n);
  // used to reconstruct where the shortest path came from
  std::vector<int> backPath(n);
  
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
        // TODO: Reconstruct path
        return estDistance[currVert];
    }
    
    // mark processed and iterate over the vertex's neighbors
    visited[currVert] = true;
    const std::list<Edge> neighbors = graph.getEdges(currVert);
    for (std::list<Edge>::const_iterator iter = neighbors.begin();
	 iter != neighbors.end(); iter++)
      {
        int vNext = iter->end;
        double dist = iter->weight;
	
        // get ready to relax the edge
        int tDist = fromDistance[currVert] + dist;
	
        // check if we should relax
        if (!visited[vNext] || tDist < fromDistance[vNext])
	  {
            backPath[vNext] = currVert;
            fromDistance[vNext] = tDist;
            // !IMPORTANT: this uses our approximation to head toward the destination
            // h*() must never overestimate the actual distance, or the algorithm may be wrong 
            estDistance[vNext] = tDist + hDijkstra();
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
  std::ifstream file("test/LargeGrid.txt");
  SparseGraph sgraph(file);
  file.close();
  
  std::cout << "Distance to end: " << aStar(sgraph, 0, 433) << "\n";
  
  return 0;
}

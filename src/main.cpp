#include <iostream>
#include <fstream>
#include <queue>
#include "SparseGraph.h"
#include "Graph.h"
#include "Heuristics.h"

int dijkstra(Vertex start, Vertex end) {
  std::list<Edge> edges = start.getEdges();
  return 0;    
}

int aStar(Vertex start, Vertex end) {
  std::vector<bool> visited(n, false); //nodes that have been visited
  //this is used in calculating the estimated, showing how far we've already traveled
  std::vector<int> fromDistance(n); 
  //this is the estimated distance from start to end
  std::vector<int> estDistance(n);
  std::vector<int> backPath(n);

  //the priority queue
  //TODO: make the priority queue a min head based off of fromDistance
  std::priority_queue<int> toVisit;
  while(!toVisit.empty()) 
  {
    //pop and relax
    int currVert = toVisit.pop();
    if (currVert == end)
    {
        return path();
    }

    visited[currVert] = true;
    std::vector<int> neighbors = graph.find(curr).getEdges();
    for (std::vector<int>::const_iterator iter = neighbors.begin();
            iter != neighbors.end(); iter++)
    {
        if (visited[*iter]) continue;
        int tDist = fromDistance[currVert] + weight(currVert, *iter);

        if (!toVisit.contains(*iter) || tDist < fromDistance[*iter])
        {
            backPath[*iter] = currVect;
            fromDistance[*iter] = tDist;
            estDistance[*iter] = tDist + hDist(*iter, end);
            if (!toVisit.contains(*iter))
            {
                toVisit.push(*iter);
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

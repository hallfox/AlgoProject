#ifndef __HEURISTICS_H
#define __HEURISTICS_H

#include <cmath>
#include <cstdlib>
#include "SparseGraph.h"
#include <vector>

int hDijkstra() { return 0; }

int hAStarGrid(int start, int end, int width, int height) { //only to be used on grid-shaped graphs
  int startx = start%width;
  int starty = height/start;
  int endx = end%width;
  int endy = height/end;
  return (int)sqrt(pow(endx-startx, 2) + pow(endy - starty, 2));
}

int hManhattan(int start, int end, int width, int height) { //only to be used on grid-shaped graphs
  int startx = start%width;
  int starty = height/start;
  int endx = end%width;
  int endy = height/end;
  return abs(endx - startx) + abs(endy - starty);
}

double hIncomingEdges(int end) { //not sure exactly how well this will work with our weights and the fact that all our other heuristics so far return ints
  Vertex *v = SparseGraph::find(end); //need sparse graph object for this to work, so I included the SparseGraph.h file. but not sure how exactly to get the right graph
  std::vector<Edge> inEdges = v->getInEdges();
  int minIndex = 0;
  for(int i = 1; i < inEdges.size(); i++) {
    if(inEdges[i] < inEdges[minIndex]) minIndex = i;
  }
  return inEdges[minIndex].weight;
}

int hAStarRand() { //may not run as accurately as other heuristics
  return rand();
}

#endif

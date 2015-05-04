#ifndef __HEURISTICS_H
#define __HEURISTICS_H

#include <cmath>
#include <cstdlib>
#include "SparseGraph.h"
#include <vector>

int hDijkstra() { return 0; }

double hAStarGrid(int start, int end, int width, int height) { //only to be used on grid-shaped graphs
  int startx = start%width;
  int starty = start/height;
  int endx = end%width;
  int endy = end/height;
  return sqrt(pow(endx-startx, 2) + pow(endy - starty, 2));
}

int hManhattan(int start, int end, int width, int height) { //only to be used on grid-shaped graphs
  int startx = start%width;
  int starty = start/height;
  int endx = end%width;
  int endy = end/height;
  return abs(endx - startx) + abs(endy - starty);
}

double hIncomingEdges(SparseGraph sg, int end) { //not sure exactly how well this will work with our weights and the fact that all our other heuristics so far return ints
  Vertex *v = sg.find(end); //need sparse graph object for this to work, so I included the SparseGraph.h file. but not sure how exactly to get the right graph
  std::list<Edge> inEdges = v->getInEdges();
  Edge min = inEdges.front();
  for(std::list<Edge>::iterator iter = inEdges.begin();
          iter != inEdges.end(); iter++)
  {
    if(*iter < min) min = *iter;
  }
  return min.weight;
}

double hAStarRand() { //may not run as accurately as other heuristics
  return rand();
}

#endif

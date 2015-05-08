#ifndef __HEURISTICS_H
#define __HEURISTICS_H

#include <cmath>
#include <cstdlib>
#include "Graph.h"
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

double hIncomingEdges(Graph &sg, int end) { //slow and inefficient, but correct, heuristic
  Vertex *v = sg.find(end);
  std::list<Edge> inEdges = v->getInEdges();
  Edge min = inEdges.front();
  for(std::list<Edge>::iterator iter = inEdges.begin();
          iter != inEdges.end(); iter++)
  {
    if((min.weight == 0) || ((*iter).weight == 0)) return 0;
    if(*iter < min) min = *iter;
  }
  return min.weight;
}

double hAStarRand() { //may not run as accurately as other heuristics
  return rand();
}

#endif

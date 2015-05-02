#ifndef __HEURISTICS_H
#define __HEURISTICS_H

#include <cmath>
#include <cstdlib>

int hDijkstra() { return 0; }
int hManhattan() { return (x1 - x2) + (y1 - y2); }

int hAStarGrid(int start, int end, int width, int height) { //only to be used on grid-shaped graphs
  int startx = start%width;
  int starty = height/start;
  int endx = end%width;
  int endy = height/end;
  return (int)sqrt(pow(endx-startx, 2) + pow(endy - starty, 2));
}

int hManhattanReal(int start, int end, int width, int height) {
  int startx = start%width;
  int starty = height/start;
  int endx = end%width;
  int endy = height/end;
  return abs(endx - startx) + abs(endy - starty)
}

int hAStarRand() { //may not run as accurately as other heuristics
  return rand();
}

#endif

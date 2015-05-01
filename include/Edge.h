#ifndef EDGE_H
#define EDGE_H

typedef struct {
  int start;
  int end;
  double weight;
  bool operator<(const Edge &other) {
    return weight < other.weight;
  }
  bool operator>(const Edge &other) {
    return weight > other.weight;
  }
  bool operator==(const Edge &other) {
    return (start == other.start) && (end == other.end) && (weight == other.weight);
  }
  bool operator<=(const Edge &other) {
    return !(*this > other);
  }
  bool operator>=(const Edge &other) {
    return !(*this < other);
  }
} Edge;

#endif

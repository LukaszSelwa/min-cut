#ifndef VERTICES_H
#define VERTICES_H
#include <iostream>
#include <vector>

namespace graphs {

class WeightedEdge {
  public:
    int srcIdx;
    int destIdx;
    int weight;

    WeightedEdge(int srcIdx, int destIdx, int weight): srcIdx(srcIdx), destIdx(destIdx), weight(weight) { }
    WeightedEdge(int srcIdx, int destIdx): srcIdx(srcIdx), destIdx(destIdx), weight(1) { }
    WeightedEdge(): WeightedEdge(0, 0, 0) { }
    bool IsEqual(const WeightedEdge & e);
    friend std::ostream & operator<< (std::ostream &os, const WeightedEdge & e);
};

class Vertice {
    int myIdx;

  public:
    std::vector<WeightedEdge> neighbors;
    
    Vertice(): myIdx(0), neighbors(std::vector<WeightedEdge>(0)) { }
    int GetIdx() const;
    void SetMyIdx(int idx);
    void AddNeighbour(int idx, int weight);
};

}

#endif /* VERTICES_H */
#ifndef VERTICES
#define VERTICES
#include <vector>

namespace graphs {

class WeightedEdge {
  public:
    const int srcIdx;
    const int destIdx;
    const int weight;

    WeightedEdge(int srcIdx, int destIdx, int weight): srcIdx(srcIdx), destIdx(destIdx), weight(weight) { }
    WeightedEdge(): WeightedEdge(0, 0, 0) { }
};

class Vertice {
    int myIdx;
    std::vector<WeightedEdge> Neighbors;

  public:
    Vertice(): myIdx(0), Neighbors(std::vector<WeightedEdge>(0)) { }
    void SetMyIdx(int idx);
    void AddNeighbour(int idx, int weight);
    const std::vector<WeightedEdge> & GetNeighbors();
};

}

#endif /* VERTICES */
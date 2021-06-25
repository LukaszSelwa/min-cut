#ifndef VERTICES
#define VERTICES
#include <vector>

namespace graphs {

class WeightedEdge {
  public:
    int srcIdx;
    int destIdx;
    int weight;

    WeightedEdge(int srcIdx, int destIdx, int weight): srcIdx(srcIdx), destIdx(destIdx), weight(weight) { }
    WeightedEdge(): WeightedEdge(0, 0, 0) { }
};

class Vertice {
    int myIdx;
    std::vector<WeightedEdge> Neighbors;

  public:
    Vertice(): myIdx(0), Neighbors(std::vector<WeightedEdge>(0)) { }
    int GetIdx();
    void SetMyIdx(int idx);
    void AddNeighbour(int idx, int weight);
    std::vector<WeightedEdge> & GetNeighbors();
};

}

#endif /* VERTICES */
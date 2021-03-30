#ifndef UNDIRECTED_WEIGHTED_GRAPH
#define UNDIRECTED_WEIGHTED_GRAPH
#include <vector>

namespace graph {

class WeightedEdge {
  public:
    const int srcIdx;
    const int destIdx;
    const int weight;

    WeightedEdge(int srcIdx, int destIdx, int weight): srcIdx(srcIdx), destIdx(destIdx), weight(weight) { }
    WeightedEdge(): WeightedEdge(0, 0, 0) { }
};

class Vertice {
    std::vector<WeightedEdge> Neighbors;
  public:
    Vertice(): Neighbors(std::vector<WeightedEdge>(0)) { }

    void AddNeighbour(int idx, int weight);
    const std::vector<WeightedEdge> & GetNeighbors();
};

class UndirectedWeightedGraph {
    
};

}
#endif /* !UNDIRECTED_WEIGHTED_GRAPH */
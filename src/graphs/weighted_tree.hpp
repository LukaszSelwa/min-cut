#ifndef TREE
#define TREE
#include <vector>
#include "vertices.hpp"

namespace graphs {

class WeightedTree {
    int rootIdx;
    std::vector<Vertice> vertices;

  public:
    WeightedTree(size_t size);
    void AddEdge(int idx1, int idx2, int weight);
};

}

#endif /* TREE */
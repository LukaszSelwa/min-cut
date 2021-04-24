#ifndef TREE
#define TREE
#include <functional>
#include <vector>
#include "vertices.hpp"

namespace graphs {

class WeightedTree {
    int rootIdx;
    std::vector<Vertice> vertices;

  public:
    WeightedTree(size_t size);
    WeightedTree(): WeightedTree(0) { }
    void AddEdge(int idx1, int idx2, int weight);
    void RunPreOrder(std::function<void(Vertice&)> func);

  private:
    void RunPreOrder(int idx, int parentIdx, std::function<void(Vertice&)> func);
};

}

#endif /* TREE */
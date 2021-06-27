#ifndef TREE
#define TREE
#include <functional>
#include <vector>
#include "vertices.hpp"

namespace graphs {

class WeightedTree {
  public:
    size_t size;
    int rootIdx;
    std::vector<Vertice> vertices;
    
    WeightedTree(size_t size);
    WeightedTree(): WeightedTree(0) { }
    void AddEdge(int idx1, int idx2, int weight);
    void RunPreOrder(std::function<void(Vertice&, int)> func);
    void RunPostOrder(std::function<void(Vertice&, int)> func);

  private:
    void RunPreOrder(int idx, int parentIdx, std::function<void(Vertice&, int)> func);
    void RunPostOrder(int idx, int parentIdx, std::function<void(Vertice&, int)> func);
};

}

#endif /* TREE */
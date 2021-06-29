#ifndef TREE
#define TREE
#include <iostream>
#include <functional>
#include <vector>
#include "vertices.hpp"

namespace graphs {

class TreeVertice {
  public:
    int idx;
    WeightedEdge parentEdge;
    std::vector<WeightedEdge> children;

    TreeVertice(): idx(0), parentEdge(0, -1, 0), children(0) { }
};

class WeightedTree {
  public:
    size_t size;
    int rootIdx;
    std::vector<TreeVertice> vertices;
    
    WeightedTree(size_t size);
    WeightedTree(): WeightedTree(0) { }
    void AddChildEdge(int parent, int child, int weight);
    void RunPreOrder(std::function<void(TreeVertice&)> func);
    void RunPostOrder(std::function<void(TreeVertice&)> func);
    friend std::ostream & operator<< (std::ostream & o, const WeightedTree & tree);

  private:
    void RunPreOrder(int idx, std::function<void(TreeVertice&)> & func);
    void RunPostOrder(int idx, std::function<void(TreeVertice&)> & func);
};

}

#endif /* TREE */
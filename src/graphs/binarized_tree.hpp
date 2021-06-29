#ifndef BINARIZED_TREE_H
#define BINARIZED_TREE_H
#include "weighted_tree.hpp"
#include <memory>

namespace graphs {

struct binarized_node {
    int parentIdx;
    int children[2];
    int orgIdx;
    int weight;
    WeightedEdge* parentEdge;
    WeightedEdge* childrenEdges[2];
};

class binarized_tree {
    std::shared_ptr<WeightedTree> orgTree;
    void build_binarized(int idx, int orgIdx);
    void add_left_edge(int idx, WeightedEdge & edge);
    void add_right_edge(int idx, int orgIdx);
    int calc_weight(int idx);

  public:
    std::vector<binarized_node> vertices;
    binarized_tree(std::shared_ptr<WeightedTree> orgTree): orgTree(orgTree) { }
    void initialize();
};

}

#endif /* BINARIZED_TREE_H */
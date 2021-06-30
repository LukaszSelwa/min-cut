#ifndef BINARIZED_TREE_H
#define BINARIZED_TREE_H
#include "weighted_tree.hpp"
#include "gmw_structure.hpp"
#include <memory>

namespace graphs {

struct binarized_node {
    binarized_node *parent, *left, *right;
    int orgIdx;
    WeightedEdge parentEd, leftEd, rightEd;
    int weight;
    bool marked;
};

struct centroid {
    binarized_node *bNode;
    centroid *left, *right, *top;
};

class binarized_tree {
    std::shared_ptr<WeightedTree> orgTree;
    std::vector<binarized_node*> mapOrg;
    int unusedItr;
    void build_binarized(binarized_node *nd, int orgIdx);
    void add_left_edge(binarized_node *nd, WeightedEdge & edge);
    void add_right_edge(binarized_node *nd, int orgIdx, int edgeNr);
    int calc_weight(binarized_node *nd);
    binarized_node* find_centroid(binarized_node *nd, int weight);
    centroid* calc_centroid_decomposition(binarized_node *nd);

  public:
    std::vector<binarized_node> vertices;
    std::vector<centroid> centroids;
    binarized_tree(std::shared_ptr<WeightedTree> orgTree): orgTree(orgTree) { }
    void initialize();
    int find_bottom_crossinterested(WeightedEdge ed, std::shared_ptr<gmw_structure> gmw);
};

}

#endif /* BINARIZED_TREE_H */
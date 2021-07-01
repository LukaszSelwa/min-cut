#ifndef BINARIZED_TREE_H
#define BINARIZED_TREE_H
#include "weighted_tree.hpp"
#include "gmw_structure.hpp"
#include <memory>
#include <functional>

namespace graphs {

struct binarized_node {
    binarized_node *parent, *left, *right;
    int orgIdx;
    int weight;
    bool marked;
    postord_range orgRange;
    int postorder, preorder;

    bool is_descendant_of(binarized_node* nd);
    bool is_independent(binarized_node* nd);
};

struct centroid {
    binarized_node *bNode;
    centroid *left, *right, *top;
};

class binarized_tree {
    std::shared_ptr<WeightedTree> orgTree;
    std::shared_ptr<gmw_structure> gmw;
    std::vector<binarized_node*> mapOrg;
    int unusedItr;
    
    binarized_node* find_centroid(binarized_node *nd, int weight);
    bool is_crossinterested(binarized_node* nd1, binarized_node* nd2);
    bool is_downinterested(binarized_node* nd1, binarized_node* nd2);
    centroid* calc_centroid_decomposition(binarized_node *nd);
    int calc_weight(binarized_node *nd);
    int find_bottom_interested(centroid* c,binarized_node* nd,
                               std::function<bool(binarized_tree&,binarized_node*,binarized_node*)> is_interested);
    void add_left_edge(binarized_node *nd, WeightedEdge & edge);
    void add_right_edge(binarized_node *nd, WeightedEdge & edge);
    void build_binarized(binarized_node *nd, int orgIdx);
    void calc_order(binarized_node *nd, int & unusedPre, int &unusedPost);

  public:
    std::vector<binarized_node> vertices;
    std::vector<centroid> centroids;
    
    binarized_tree(std::shared_ptr<WeightedTree> orgTree, std::shared_ptr<gmw_structure> gmw): orgTree(orgTree), gmw(gmw) { }
    
    int find_bottom_crossinterested(WeightedEdge ed);
    int find_bottom_downinterested(WeightedEdge ed);
    void initialize();
};

}

#endif /* BINARIZED_TREE_H */
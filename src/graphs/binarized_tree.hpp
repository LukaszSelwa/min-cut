#ifndef BINARIZED_TREE_H
#define BINARIZED_TREE_H
#include <functional>
#include <memory>

#include "gmw_structure.hpp"
#include "weighted_tree.hpp"

namespace graphs {

struct binarized_node {
    binarized_node *parent = nullptr, *left = nullptr, *right = nullptr;
    int orgIdx = 0;
    int weight = 0;
    bool marked = false;
    postord_range orgRange = {0, 0};
    int postorder = 0, preorder = 0;

    bool is_descendant_of(binarized_node* nd);
    bool is_independent(binarized_node* nd);
};

struct centroid {
    binarized_node* bNode = nullptr;
    centroid *left = nullptr, *right = nullptr, *top = nullptr;
};

class binarized_tree {
    std::shared_ptr<weighted_tree> orgTree;
    std::shared_ptr<gmw_structure> gmw;
    std::vector<binarized_node*> mapOrg;
    int unusedItr;

    binarized_node* find_centroid(binarized_node* nd, int weight);
    bool is_crossinterested(binarized_node* nd1, binarized_node* nd2);
    bool is_downinterested(binarized_node* nd1, binarized_node* nd2);
    centroid* calc_centroid_decomposition(binarized_node* nd);
    int calc_weight(binarized_node* nd);
    int find_bottom_interested(
        centroid* c, binarized_node* nd,
        std::function<bool(binarized_tree&, binarized_node*, binarized_node*)> is_interested);
    void add_left_edge(binarized_node* nd, w_edge& edge);
    void add_right_edge(binarized_node* nd, w_edge& edge);
    void build_binarized(binarized_node* nd, int orgIdx);
    void calc_order(binarized_node* nd, int& unusedPre, int& unusedPost);

   public:
    std::vector<binarized_node> vertices;
    std::vector<centroid> centroids;

    binarized_tree(std::shared_ptr<weighted_tree> orgTree, std::shared_ptr<gmw_structure> gmw)
        : orgTree(orgTree), gmw(gmw) {}

    int find_bottom_crossinterested(w_edge ed);
    int find_bottom_downinterested(w_edge ed);
    void initialize();
};

}  // namespace graphs

#endif /* BINARIZED_TREE_H */
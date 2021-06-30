#include "binarized_tree.hpp"
#include <algorithm>

namespace graphs {

void binarized_tree::initialize() {
    size_t size = 0;
    for (auto & v : orgTree->vertices)
        size += std::max((size_t)1, v.children.size());
    
    vertices = std::vector<binarized_node>(size);
    mapOrg = std::vector<binarized_node*>(orgTree->size);
    unusedItr = 0;
    vertices[unusedItr++] = binarized_node{
        .parent=nullptr, .left=nullptr, .right=nullptr,
        .orgIdx=orgTree->rootIdx
    };
    build_binarized(&vertices[0], orgTree->rootIdx);

    for (auto & v : vertices)
        v.marked = false;
    centroids = std::vector<centroid>(size);
    unusedItr = 0;
    calc_centroid_decomposition(&vertices[0]);
}

void binarized_tree::build_binarized(binarized_node *nd, int orgIdx) {
    auto & v = orgTree->vertices[orgIdx];
    int degree = v.children.size();
    mapOrg[orgIdx] = nd;
    if (degree >= 1) {
        add_left_edge(nd, v.children[0]);
        build_binarized(nd->left, v.children[0].destIdx);
    }
    int i = 1;
    for (; i < degree; ++i) {
        auto & edge = v.children[i];
        add_right_edge(nd, orgIdx, i);
        nd = nd->right;
        add_left_edge(nd, edge);
        build_binarized(nd->left, edge.destIdx);
    }
}

void binarized_tree::add_left_edge(binarized_node *nd, WeightedEdge & edge) {
    vertices[unusedItr] = binarized_node{
        .parent=nd, .left=nullptr, .right=nullptr,
        .orgIdx=edge.destIdx, 
        .parentEd=edge,
    };
    nd->left = &vertices[unusedItr++];
    nd->leftEd = edge;
}

void binarized_tree::add_right_edge(binarized_node *nd, int orgIdx, int edgeNr) {
    WeightedEdge edge(orgIdx, orgIdx, edgeNr);
    vertices[unusedItr] = binarized_node{
        .parent=nd, .left=nullptr, .right=nullptr,
        .orgIdx=orgIdx,
        .parentEd=edge
    };
    nd->right = &vertices[unusedItr++];
    nd->rightEd = edge;
}

int binarized_tree::calc_weight(binarized_node *nd) {
    nd->weight = 1;
    if (nd->left != nullptr && !(nd->left->marked))
        nd->weight += calc_weight(nd->left);
    if (nd->right != nullptr && !(nd->right->marked))
        nd->weight += calc_weight(nd->right);
    return nd->weight;
}

binarized_node* binarized_tree::find_centroid(binarized_node *nd, int weight) {
    while (true) {
        if (nd->parent != nullptr && !(nd->parent->marked) 
                && 2*(weight - nd->weight) > weight) {
            nd = nd->parent;
            continue;
        }
        if (nd->left != nullptr && !(nd->left->marked) 
                && 2*(nd->left->weight) > weight) {
            nd = nd->left;
            continue;
        }
        if (nd->right != nullptr && !(nd->right->marked) 
                && 2*(nd->right->weight) > weight) {
            nd = nd->right;
            continue;
        }
        break;
    }
    return nd;
}

centroid* binarized_tree::calc_centroid_decomposition(binarized_node *nd) {
    while (nd->parent != nullptr && !(nd->parent->marked))
        nd = nd->parent;
    int weight = calc_weight(nd);
    nd = find_centroid(nd, weight);
    nd->marked = true;
    centroids[unusedItr] = centroid{
        .bNode=nd,
        .left=nullptr, .right=nullptr, .top=nullptr
    };
    centroid *c = &centroids[unusedItr++];
    
    if (nd->parent != nullptr && !(nd->parent->marked))
        c->top = calc_centroid_decomposition(nd->parent);
    if (nd->left != nullptr && !(nd->left->marked))
        c->left = calc_centroid_decomposition(nd->left);
    if (nd->right != nullptr && !(nd->right->marked))
        c->right = calc_centroid_decomposition(nd->right);
    return c;
}

int binarized_tree::find_bottom_crossinterested(WeightedEdge ed, std::shared_ptr<gmw_structure> gmw) {
    return 0;
}

}
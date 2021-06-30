#include "binarized_tree.hpp"
#include <algorithm>

namespace graphs {

bool binarized_node::is_descendant(binarized_node* nd) {
    return preorder <= nd->preorder && postorder >= nd->postorder;
}

bool binarized_node::is_independent(binarized_node* nd) {
    return !is_descendant(nd) && !nd->is_descendant(this);
}

void binarized_tree::initialize() {
    size_t size = 0;
    for (auto & v : orgTree->vertices)
        size += std::max((size_t)1, v.children.size());
    
    vertices = std::vector<binarized_node>(size);
    mapOrg = std::vector<binarized_node*>(orgTree->size);
    unusedItr = 0;
    vertices[unusedItr++] = binarized_node{
        .parent=nullptr, .left=nullptr, .right=nullptr,
        .orgIdx=orgTree->rootIdx,
        .orgRange=gmw->postorder[orgTree->rootIdx]
    };
    build_binarized(&vertices[0], orgTree->rootIdx);

    for (auto & v : vertices)
        v.marked = false;
    centroids = std::vector<centroid>(size);
    unusedItr = 0;
    calc_centroid_decomposition(&vertices[0]);

    int unusedPre = 1, unusedPost = 1;
    calc_order(&vertices[0], unusedPre, unusedPost);
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
        add_right_edge(nd, edge);
        nd = nd->right;
        add_left_edge(nd, edge);
        build_binarized(nd->left, edge.destIdx);
    }
}

void binarized_tree::add_left_edge(binarized_node *nd, WeightedEdge & edge) {
    vertices[unusedItr] = binarized_node{
        .parent=nd, .left=nullptr, .right=nullptr,
        .orgIdx=edge.destIdx, 
        .orgRange=gmw->postorder[edge.destIdx]
    };
    nd->left = &vertices[unusedItr++];
}

void binarized_tree::add_right_edge(binarized_node *nd, WeightedEdge & edge) {
    vertices[unusedItr] = binarized_node{
        .parent=nd, .left=nullptr, .right=nullptr,
        .orgIdx=edge.srcIdx,
        .orgRange=postord_range{
            .begin=gmw->postorder[edge.destIdx].begin, 
            .end=gmw->postorder[edge.srcIdx].end
        }
    };
    nd->right = &vertices[unusedItr++];
}

int binarized_tree::calc_weight(binarized_node *nd) {
    nd->weight = 1;
    if (nd->left != nullptr && !(nd->left->marked))
        nd->weight += calc_weight(nd->left);
    if (nd->right != nullptr && !(nd->right->marked))
        nd->weight += calc_weight(nd->right);
    return nd->weight;
}

void binarized_tree::calc_order(binarized_node *nd, int & unusedPre, int &unusedPost) {
    nd->preorder = unusedPre++;
    if (nd->left != nullptr)
        calc_order(nd->left, unusedPre, unusedPost);
    if (nd->right != nullptr)
        calc_order(nd->right, unusedPre, unusedPost);
    nd->postorder = unusedPost++;
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

bool binarized_tree::is_crossinterested(binarized_node* nd1, binarized_node* nd2) {
    return !nd2->is_descendant(nd1) && gmw->is_crossinterested(nd1->orgIdx, nd2->orgRange);
}

int binarized_tree::find_bottom_crossinterested(WeightedEdge ed) {
    int idx = gmw->get_lower_endpoint(ed);
    centroid *c = &centroids[0];
    binarized_node *nd = mapOrg[idx];
    while (true) {
        if (c->left != nullptr && is_crossinterested(nd, c->bNode->left)) {
            c = c->left;
            continue;
        }
        if (c->right != nullptr && is_crossinterested(nd, c->bNode->right)) {
            c = c->right;
            continue;
        }
        if (c->top != nullptr) {
            c = c->top;
            continue;
        }
        break;
    }
    binarized_node* interestedNd = c->bNode;
    if (interestedNd->left != nullptr && is_crossinterested(nd, interestedNd->left))
        interestedNd = interestedNd->left;
    return interestedNd->orgIdx;
}

}
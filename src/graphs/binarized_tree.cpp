#include "binarized_tree.hpp"

namespace graphs {

void binarized_tree::initialize() {
    vertices = std::vector<binarized_node>{binarized_node{
        .parentIdx = -1,
        .children={-1, -1},
        .orgIdx=orgTree->rootIdx, 
        .parentEdge=nullptr,
        .childrenEdges={nullptr, nullptr}
    }};
    build_binarized(0, orgTree->rootIdx);
    calc_weight(0);
}

void binarized_tree::build_binarized(int idx, int orgIdx) {
    auto & v = orgTree->vertices[orgIdx];
    int degree = v.children.size();
    if (degree >= 1) {
        add_left_edge(idx, v.children[0]);
        build_binarized(vertices[idx].children[0], v.children[0].destIdx);
    }
    int i = 1;
    for (; i < degree; ++i) {
        auto & edge = v.children[i];
        add_right_edge(idx, orgIdx);
        idx = vertices[idx].children[1];
        add_left_edge(idx, edge);
        build_binarized(vertices[idx].children[0], edge.destIdx);
    }
}

void binarized_tree::add_left_edge(int idx, WeightedEdge & edge) {
    vertices[idx].children[0] = vertices.size();
    vertices[idx].childrenEdges[0] = &(edge);
    vertices.push_back(binarized_node{
        .parentIdx = idx,
        .children={-1, -1},
        .orgIdx=edge.destIdx, 
        .parentEdge=&(edge),
        .childrenEdges={nullptr, nullptr}
    });
}

void binarized_tree::add_right_edge(int idx, int orgIdx) {
    vertices[idx].children[1] = vertices.size();
    vertices[idx].childrenEdges[1] = nullptr;
    vertices.push_back(binarized_node{
        .parentIdx = idx,
        .children={-1, -1},
        .orgIdx=orgIdx,
        .parentEdge = nullptr,
        .childrenEdges={nullptr, nullptr}
    });
}

int binarized_tree::calc_weight(int idx) {
    vertices[idx].weight = 1;
    for (int i = 0; i < 2; ++i) {
        if (vertices[idx].children[i] != -1)
            vertices[idx].weight += calc_weight(vertices[idx].children[i]);
    }
    return vertices[idx].weight;
}

}
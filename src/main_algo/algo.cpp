#include "algo.hpp"

#include <functional>
#include <iostream>
#include <limits>

#include "../monge_matrix_min/partial_monge_min.hpp"

algo::algo(std::shared_ptr<graphs::weighted_graph> graph,
           std::shared_ptr<graphs::weighted_tree> tree)
    : graph(graph), tree(tree) {}

void algo::initialize_structures() {
    gmw = std::make_shared<gmw_structure>(
        std::make_unique<Interval2DTree>(graph->size + 1, graph->size + 1));
    gmw->initialize(graph, tree);
    graphs::binarized_tree bTree(tree, gmw);
    bTree.initialize();
    for (auto& v : tree->vertices) {
        if (v.idx != tree->rootIdx) {
            v.bottomCrossinterested = bTree.find_bottom_crossinterested(v.parentEdge);
            v.bottomDowninterested = bTree.find_bottom_downinterested(v.parentEdge);
        }
    }
    hld = std::make_shared<graphs::hl_decomposition>(tree);
    hld->initialize(gmw);
}

edge_pair algo::find_1respect_cut() {
    // TODO
    return edge_pair{.e1 = graphs::w_edge(0, 0), .e2 = NIL_EDGE};
}

edge_pair algo::find_2respect_cut_in_single_hl_path(int pathIdx) {
    auto& edges = hld->paths[pathIdx].edges;
    auto size = edges.size();
    if (size <= 1)
        return edge_pair{.e1 = NIL_EDGE, .e2 = NIL_EDGE, .val = std::numeric_limits<int>::max()};

    std::function<int(size_t, size_t)> lookup = [&](size_t i, size_t j) -> int {
        return gmw->get_cut_val(edges[i], edges[size - 1 - j]);
    };
    min_coords cords = partial_monge_min(edges.size() - 1, lookup);
    cords.col = size - 1 - cords.col;
    return edge_pair{.e1 = edges[cords.row], .e2 = edges[cords.col], .val = cords.val};
}

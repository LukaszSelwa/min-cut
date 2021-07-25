#include "algo.hpp"

#include <functional>
#include <limits>

#include "../monge_matrix_min/partial_monge_min.hpp"

algo::algo(std::shared_ptr<graphs::weighted_graph> graph,
           std::shared_ptr<graphs::weighted_tree> tree)
    : graph(graph), tree(tree) {}

void algo::initialize_structures() {
    gmw = std::make_shared<gmw_structure>(
        std::make_unique<Interval2DTree>(graph->size + 1, graph->size + 1));
    gmw->initialize(graph, tree);
    bTree = std::make_shared<graphs::binarized_tree>(tree, gmw);
    bTree->initialize();
    hld = std::make_shared<graphs::hl_decomposition>(tree);
    hld->initialize(gmw);
}

edge_pair algo::find_1respect_cut() {
    // TODO
    return edge_pair{.e1 = graphs::w_edge(0, 0), .e2 = NIL_EDGE};
}

edge_pair algo::find_2respect_cut_in_single_hl_path(int pathIdx) {
    auto& edges = hld->paths[pathIdx].edges;
    std::function<int(size_t, size_t)> lookup = [&](size_t i, size_t j) -> int {
        return gmw->get_cut_val(edges[i], edges[j]);
    };
    if (edges.size() <= 1)
        return edge_pair{.e1 = NIL_EDGE, .e2 = NIL_EDGE, .val = std::numeric_limits<int>::max()};
    min_coords cords = partial_monge_min(edges.size(), lookup);
    return edge_pair{.e1 = edges[cords.row], .e2 = edges[cords.col], .val = cords.val};
}

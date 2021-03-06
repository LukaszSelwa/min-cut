#include "gmw_algo.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>

#include "../monge_matrix_min/partial_monge_min.hpp"

gmw_algo::gmw_algo(std::shared_ptr<graphs::weighted_graph> graph,
                   std::shared_ptr<graphs::weighted_tree> tree)
    : graph(graph), tree(tree) {}

void gmw_algo::initialize() {
    gmw = std::make_shared<gmw_structure>(std::make_unique<segment_2d_point_tree>(graph->size + 1));
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

edge_pair gmw_algo::find_1respect_cut() {
    auto& subtreeCost = gmw->subtreeCost;
    auto minIdx = std::min_element(subtreeCost.begin(), subtreeCost.end()) - subtreeCost.begin();

    return edge_pair{
        .e1 = tree->vertices[minIdx].parentEdge,
        .e2 = tree->vertices[minIdx].parentEdge,
        .val = subtreeCost[minIdx],
    };
}

edge_pair gmw_algo::find_2respect_cut_single(int pathIdx) {
    auto& edges = hld->paths[pathIdx].edges;
    auto size = edges.size();
    if (size <= 1)
        return edge_pair{.e1 = NIL_EDGE, .e2 = NIL_EDGE, .val = std::numeric_limits<int>::max()};

    std::function<int(size_t, size_t)> lookup = [&](size_t i, size_t j) -> int {
        return gmw->get_cut_val(edges[i], edges[size - 1 - j]);
    };
    min_coords coords = partial_monge_min(edges.size() - 1, lookup);
    coords.col = size - 1 - coords.col;
    return edge_pair{.e1 = edges[coords.row], .e2 = edges[coords.col], .val = coords.val};
}

edge_pair gmw_algo::find_2respect_cut_single() {
    edge_pair result{.val = std::numeric_limits<int>::max()};
    for (int pathIdx = 0; pathIdx < hld->paths.size(); ++pathIdx)
        result = std::min(result, find_2respect_cut_single(pathIdx));
    return result;
}

edge_pair gmw_algo::find_2respect_cut_pair(graphs::interested_path_pair& paths) {
    auto& edgesP = paths.edgesP;
    auto& edgesQ = paths.edgesQ;
    auto rows = edgesP.size();
    auto cols = edgesQ.size();
    std::function<int(size_t, size_t)> lookup = [&](size_t i, size_t j) -> int {
        return gmw->get_cut_val(edgesP[i], edgesQ[cols - 1 - j]);
    };
    min_coords coords = smawk_min(rows, cols, lookup);
    coords.col = cols - 1 - coords.col;
    return edge_pair{.e1 = edgesP[coords.row], .e2 = edgesQ[coords.col], .val = coords.val};
}

edge_pair gmw_algo::find_2respect_cut_pair() {
    edge_pair result{.val = std::numeric_limits<int>::max()};
    for (auto& paths : hld->interesting_pairs)
        result = std::min(result, find_2respect_cut_pair(paths));
    return result;
}

edge_pair gmw_algo::find_cut() {
    std::vector<edge_pair> cuts{
        find_1respect_cut(),
        find_2respect_cut_single(),
        find_2respect_cut_pair(),
    };
    auto min = std::min_element(cuts.begin(), cuts.end());
    return *min;
}
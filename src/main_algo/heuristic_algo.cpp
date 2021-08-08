#include "heuristic_algo.hpp"

#include <algorithm>
#include <functional>
#include <limits>

#include "../spanning_trees_extractors/random_spanning_trees_extractor.hpp"
#include "../utils/functions.hpp"
#include "gmw_algo.hpp"

namespace heuristic {
algo::algo(std::shared_ptr<graphs::weighted_graph> graph) : graph(graph) {}

size_t algo::get_iterations_nr() { return std::max((size_t)10, log_ceil(graph->size)); }

algo_result algo::run_iteration(std::shared_ptr<std::mt19937> seed) {
    auto tree =
        std::make_shared<graphs::weighted_tree>(extractSingleRandomSpanningTree(*graph, seed));
    gmw_algo algo(graph, tree);
    algo.initialize();
    auto cut = algo.find_cut();
    return algo_result{
        .minCutVal = cut.val,
        .cut = get_cut(tree, cut),
    };
}

std::vector<bool> algo::get_cut(std::shared_ptr<graphs::weighted_tree> tree,
                                edge_pair cut2respect) {
    std::vector<bool> cut(tree->size, false);
    std::vector<bool> visited(tree->size, false);

    std::function<void(int, bool)> dfs = [&](int vIdx, bool mark) {
        visited[vIdx] = true;
        cut[vIdx] = mark;
        auto& v = tree->vertices[vIdx];
        for (auto& e : v.children) {
            if (e.is_equal(cut2respect.e1) || e.is_equal(cut2respect.e2))
                dfs(e.destIdx, !mark);
            else
                dfs(e.destIdx, mark);
        }
    };

    dfs(tree->rootIdx, true);

    return cut;
}

algo_result algo::calc_min_cut() {
    algo_result result{.minCutVal = std::numeric_limits<int>::max()};
    size_t iterations = get_iterations_nr();
    auto seed = std::make_shared<std::mt19937>();

    for (size_t i = 0; i < iterations; ++i) {
        auto nResult = run_iteration(seed);
        if (nResult.minCutVal < result.minCutVal) result = nResult;
    }

    return result;
}

}  // namespace heuristic
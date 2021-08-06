#include "naive_algo.hpp"

#include <limits>

namespace naive {

algo::algo(std::shared_ptr<graphs::weighted_graph> graph) : graph(graph), fg(graph->size) {}

void algo::translate_graph() {
    for (auto& v : graph->vertices) {
        for (auto& e : v.neighbors) {
            if (e.srcIdx < e.destIdx) fg.add_edge(e.srcIdx, e.destIdx, e.weight);
        }
    }
}

algo_result algo::calc_min_cut() {
    translate_graph();
    algo_result result{.minCutVal = std::numeric_limits<int>::max()};
    auto n = graph->size;

    fg.set_source(0);
    int sink;
    int cutVal;
    std::vector<bool> cut;
    for (sink = 1; sink < n; ++sink) {
        fg.clear_flow();
        fg.set_sink(sink);

        cutVal = fg.calc_max_flow();
        if (cutVal < result.minCutVal) {
            result = algo_result{.minCutVal = cutVal, .cut = fg.get_min_cut()};
        }
    }
    return result;
}

}  // namespace naive
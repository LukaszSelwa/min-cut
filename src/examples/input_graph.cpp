#include "input_graph.hpp"

namespace examples {
using namespace graphs;

input_graph input_graph::make_copy() {
    return input_graph{.graph = std::make_shared<weighted_graph>(*graph),
                       .spanningTree = std::make_shared<weighted_tree>(*spanningTree),
                       .expectedMinCut = expectedMinCut};
}

input_graph read_form_in(std::istream& in) {
    input_graph ig;
    size_t n;
    size_t m;
    int from, to, weight;
    in >> n >> m;
    ig.graph = std::make_shared<weighted_graph>(n);
    ig.spanningTree = std::make_shared<weighted_tree>(n);

    for (size_t i = 0; i < m; ++i) {
        in >> from >> to >> weight;
        ig.graph->add_edge(w_edge(from, to, weight));
    }

    for (size_t i = 0; i < n - 1; ++i) {
        in >> from >> to >> weight;
        ig.spanningTree->add_child_edge(from, to, weight);
    }

    in >> ig.expectedMinCut;

    return ig;
}

}  // namespace examples
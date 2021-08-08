#include "edge_cases.hpp"

std::shared_ptr<graphs::weighted_graph> generate_ladder_graph(size_t height, int edgeWeight,
                                                              int levelWeight) {
    auto graph = std::make_shared<graphs::weighted_graph>(2 * height);

    graph->add_edge(graphs::w_edge(0, 1, levelWeight));

    for (size_t level = 1; level < height; ++level) {
        graph->add_edge(graphs::w_edge(2 * level - 2, 2 * level, edgeWeight));
        graph->add_edge(graphs::w_edge(2 * level - 1, 2 * level + 1, edgeWeight));
        graph->add_edge(graphs::w_edge(2 * level, 2 * level + 1, levelWeight));
    }
    return graph;
}
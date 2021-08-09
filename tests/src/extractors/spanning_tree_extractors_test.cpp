#include <gtest/gtest.h>

#include "../../../src/spanning_trees_extractors/random_spanning_trees_extractor.hpp"

TEST(RandomSpanningTreeExtractors, WeightedSpanningTree) {
    auto seed = std::make_shared<std::mt19937>();
    auto graph = std::make_shared<graphs::weighted_graph>(4);
    graph->add_edge(graphs::w_edge(0, 1, 10000));
    graph->add_edge(graphs::w_edge(0, 2, 10000));
    graph->add_edge(graphs::w_edge(0, 3, 10000));
    graph->add_edge(graphs::w_edge(1, 2, 1));
    graph->add_edge(graphs::w_edge(1, 3, 1));
    graph->add_edge(graphs::w_edge(2, 3, 1));

    auto tree = extractSingleRandomWeightedSpanningTree(graph, seed);
    EXPECT_EQ(tree->vertices[0].children.size(), 3);
}
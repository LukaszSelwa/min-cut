#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <random>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graphs/random_graph_generation.hpp"
#include "../../../src/main_algo/algo.hpp"
#include "../../../src/spanning_trees_extractors/random_spanning_trees_extractor.hpp"

TEST(MainAlgo_FindCut, SmallExample_1) {
    auto example = examples::get_example(1);

    algo al(example.graph, example.spanningTree);
    al.initialize_structures();
    auto res = al.find_cut();
    EXPECT_EQ(res.val, 4);
    EXPECT_EQ(res.e1, graphs::w_edge(6, 5));
    EXPECT_EQ(res.e2, graphs::w_edge(2, 1));
}
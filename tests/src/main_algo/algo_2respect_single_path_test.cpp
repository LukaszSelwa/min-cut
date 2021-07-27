#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <random>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graphs/random_graph_generation.hpp"
#include "../../../src/main_algo/algo.hpp"
#include "../../../src/spanning_trees_extractors/random_spanning_trees_extractor.hpp"

TEST(MainAlgo_2respectSinglePath, SmallExample_1) {
    auto example = examples::get_example(1);

    algo al(example.graph, example.spanningTree);
    al.initialize_structures();
    auto res = al.find_2respect_cut_in_single_hl_path(0);
    EXPECT_EQ(res.val, 8);
    EXPECT_EQ(res.e1, graphs::w_edge(7, 3));
    EXPECT_EQ(res.e2, graphs::w_edge(3, 2));

    res = al.find_2respect_cut_in_single_hl_path(1);
    EXPECT_EQ(res.val, 6);
    EXPECT_EQ(res.e1, graphs::w_edge(6, 5));
    EXPECT_EQ(res.e2, graphs::w_edge(5, 1));

    res = al.find_2respect_cut_in_single_hl_path(2);
    EXPECT_EQ(res.val, std::numeric_limits<int>::max());
    EXPECT_EQ(res.e1, NIL_EDGE);
    EXPECT_EQ(res.e2, NIL_EDGE);
}

TEST(MainAlgo_2respectSinglePath, SmallExample_2) {
    auto example = examples::get_example(2);

    algo al(example.graph, example.spanningTree);
    al.initialize_structures();
    auto res = al.find_2respect_cut_in_single_hl_path(0);
    EXPECT_EQ(res.val, 1);
    EXPECT_EQ(res.e1, graphs::w_edge(1, 4));
    EXPECT_EQ(res.e2, graphs::w_edge(4, 9));

    res = al.find_2respect_cut_in_single_hl_path(5);
    EXPECT_EQ(res.val, 18);
    EXPECT_EQ(res.e1, graphs::w_edge(2, 6));
    EXPECT_EQ(res.e2, graphs::w_edge(6, 0));
}

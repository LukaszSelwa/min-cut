#include <gtest/gtest.h>

#include <iostream>

#include "../../../src/graph_generation/random_graph_generation.hpp"
#include "../../../src/naive_algo/naive_algo.hpp"

TEST(Genreate_RandomGraph, Example) {
    auto seed = std::make_shared<std::mt19937>();
    auto graph =
        graphs::generate_random_graph(std::vector<bool>{1, 1, 1, 1, 0, 0, 0}, 18, 5, 2, seed);
    auto cut = naive::algo(graph).calc_min_cut();
    EXPECT_EQ(cut.minCutVal, 18) << *graph;
    bool verify = cut.cut == std::vector<bool>{1, 1, 1, 1, 0, 0, 0} ||
                  cut.cut == std::vector<bool>{0, 0, 0, 0, 1, 1, 1};
    EXPECT_TRUE(verify) << *graph;
}
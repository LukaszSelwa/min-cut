#include <gtest/gtest.h>

#include <iostream>

#include "../../../src/graph_generation/random_graph_generation.hpp"
#include "../../../src/naive_algo/naive_algo.hpp"

TEST(Genreate_RandomGraph, Example1) {
    auto seed = std::make_shared<std::mt19937>();
    auto graph =
        graphs::generate_random_graph(std::vector<bool>{1, 1, 1, 1, 0, 0, 0}, 18, 5, 2, seed);
    auto cut = naive::algo(graph).calc_min_cut();
    EXPECT_EQ(cut.minCutVal, 18) << *graph;
    bool verify = cut.cut == std::vector<bool>{1, 1, 1, 1, 0, 0, 0} ||
                  cut.cut == std::vector<bool>{0, 0, 0, 0, 1, 1, 1};
    EXPECT_TRUE(verify) << *graph;
}

TEST(Genreate_RandomGraph, Example2) {
    auto seed = std::make_shared<std::mt19937>();
    auto input = graphs::generate_random_graph_input(8, 3, 7, 2, 15, seed);

    int trues = 0;
    for (bool c : input.minCut) trues += int(c);
    EXPECT_EQ(trues, 3);

    int cutEdges = 0;
    int cutVal = 0;
    for (auto& v : input.graph->vertices) {
        for (auto& e : v.neighbors) {
            if (input.minCut[e.srcIdx] && !input.minCut[e.destIdx]) {
                cutEdges++;
                cutVal += e.weight;
            }
        }
    }
    EXPECT_EQ(cutEdges, 7);
    EXPECT_EQ(cutVal, 15);
}

TEST(Genreate_RandomGraph, Example3) {
    auto seed = std::make_shared<std::mt19937>();
    auto input = graphs::generate_fully_random_graph_input(3, 12, 40, 2, 2, seed);

    EXPECT_LE(input.graph->size, 12);
}
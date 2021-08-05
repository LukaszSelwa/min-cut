#include <gtest/gtest.h>

#include <vector>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/main_algo/karger_algo.hpp"

TEST(KargerAlgo_Costs, SubtreeSmallExample_1) {
    auto example = examples::get_example(1);

    karger_algo algo(example.graph, example.spanningTree);
    algo.initialize();

    std::vector<int> expSubtreeCost{0, 5, 10, 9, 6, 12, 8, 5};
    EXPECT_EQ(algo.subtreeCost, expSubtreeCost);
}

TEST(KargerAlgo_Costs, PairSmallExample_1) {
    auto example = examples::get_example(1);

    karger_algo algo(example.graph, example.spanningTree);
    algo.initialize();

    /* clang-format off */
    std::vector<std::vector<int>> expPairCost{
        {54, 43, 22, 13,  6, 14,  8,  5},
        {43, 38, 22, 13,  3, 11,  8,  5},
        {22, 22, 12,  8,  0,  7,  7,  2},
        {13, 13,  8,  4,  0,  5,  5,  2},
        { 6,  3,  0,  0,  0,  3,  0,  0},
        {14, 11,  7,  5,  3,  2,  1,  3},
        { 8,  8,  7,  5,  0,  1,  0,  3},
        { 5,  5,  2,  2,  0,  3,  3,  0},
    };
    /* clang-format on */
    EXPECT_EQ(algo.pairCost, expPairCost);
}
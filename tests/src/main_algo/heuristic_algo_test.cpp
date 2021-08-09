#include "../../../src/main_algo/heuristic_algo.hpp"

#include <gtest/gtest.h>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graph_generation/random_graph_generation.hpp"

TEST(MainAlgo_Heuristic, SmallExample_1) {
    auto example = examples::get_example(1);

    heuristic::algo algo(example.graph);
    auto res = algo.calc_min_cut();
    EXPECT_EQ(res.minCutVal, 4);
    std::vector<bool> expCut{1, 1, 0, 0, 1, 1, 0, 0};
    EXPECT_EQ(res.cut, expCut);
}

TEST(MainAlgo_Heuristic, SmallExample_2) {
    auto example = examples::get_example(2);

    heuristic::algo algo(example.graph);
    auto res = algo.calc_min_cut();
    EXPECT_EQ(res.minCutVal, 1);
    std::vector<bool> expCut{1, 0, 1, 1, 1, 1, 1, 1, 1, 1};
    EXPECT_EQ(res.cut, expCut);
}

TEST(MainAlgo_Heuristic, SmallExample_3) {
    auto example = examples::get_example(3);

    heuristic::algo algo(example.graph);
    auto res = algo.calc_min_cut();
    EXPECT_EQ(res.minCutVal, 4);
    std::vector<bool> expCut{1, 1, 1, 0, 1, 1, 1};
    EXPECT_EQ(res.cut, expCut);
}

TEST(MainAlgo_Heuristic, SmallExample_4) {
    auto example = examples::get_example(4);

    heuristic::algo algo(example.graph);
    auto res = algo.calc_min_cut();
    EXPECT_EQ(res.minCutVal, 28);
    std::vector<bool> expCut{1, 1, 1, 1, 1, 0, 1};
    EXPECT_EQ(res.cut, expCut);
}

TEST(MainAlgo_Heuristic, SmallExample_5) {
    auto example = examples::get_example(5);

    heuristic::algo algo(example.graph);
    auto res = algo.calc_min_cut();
    EXPECT_EQ(res.minCutVal, 17);
    std::vector<bool> expCut{1, 1, 1, 0, 1, 1};
    EXPECT_EQ(res.cut, expCut);
}

TEST(MainAlgo_Heuristic, SmallExample_6) {
    auto example = examples::get_example(6);

    heuristic::algo algo(example.graph);
    auto res = algo.calc_min_cut();
    EXPECT_EQ(res.minCutVal, 14);
}
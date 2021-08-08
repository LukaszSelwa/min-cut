#include <gtest/gtest.h>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graph_generation/random_graph_generation.hpp"
#include "../../../src/naive_algo/naive_algo.hpp"

TEST(NaiveAlgo_Algo, SmallExample_1) {
    auto example = examples::get_example(1);

    naive::algo algo(example.graph);
    auto res = algo.calc_min_cut();
    EXPECT_EQ(res.minCutVal, 4);
    std::vector<bool> expCut{1, 1, 0, 0, 1, 1, 0, 0};
    EXPECT_EQ(res.cut, expCut);
}

TEST(NaiveAlgo_Algo, SmallExample_2) {
    auto example = examples::get_example(2);

    naive::algo algo(example.graph);
    auto res = algo.calc_min_cut();
    EXPECT_EQ(res.minCutVal, 1);
    std::vector<bool> expCut{1, 0, 1, 1, 1, 1, 1, 1, 1, 1};
    EXPECT_EQ(res.cut, expCut);
}

TEST(NaiveAlgo_Algo, SmallExample_3) {
    auto example = examples::get_example(3);

    naive::algo algo(example.graph);
    auto res = algo.calc_min_cut();
    EXPECT_EQ(res.minCutVal, 4);
    std::vector<bool> expCut{1, 1, 1, 0, 1, 1, 1};
    EXPECT_EQ(res.cut, expCut);
}

TEST(NaiveAlgo_Algo, SmallExample_4) {
    auto example = examples::get_example(4);

    naive::algo algo(example.graph);
    auto res = algo.calc_min_cut();
    EXPECT_EQ(res.minCutVal, 28);
    std::vector<bool> expCut{1, 1, 1, 1, 1, 0, 1};
    EXPECT_EQ(res.cut, expCut);
}

TEST(NaiveAlgo_Algo, SmallExample_5) {
    auto example = examples::get_example(5);

    naive::algo algo(example.graph);
    auto res = algo.calc_min_cut();
    EXPECT_EQ(res.minCutVal, 17);
    std::vector<bool> expCut{1, 1, 1, 0, 1, 1};
    EXPECT_EQ(res.cut, expCut);
}
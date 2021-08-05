#include <gtest/gtest.h>

#include <vector>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/main_algo/karger_algo.hpp"
#include "../utils/brut_find_cut.hpp"

TEST(KargerAlgo_FindCost, SmallExample_1) {
    auto example = examples::get_example(1);

    karger_algo algo(example.graph, example.spanningTree);
    algo.initialize();
    auto res = algo.find_cut();
    EXPECT_EQ(res.val, 4);
    EXPECT_EQ(res.e1, graphs::w_edge(2, 1));
    EXPECT_EQ(res.e2, graphs::w_edge(6, 5));
}

TEST(KargerAlgo_FindCost, SmallExample_2) {
    auto example = examples::get_example(2);

    karger_algo algo(example.graph, example.spanningTree);
    algo.initialize();
    auto res = algo.find_cut();
    EXPECT_EQ(res.val, 1);
    EXPECT_EQ(res.e1, graphs::w_edge(1, 4));
    EXPECT_EQ(res.e2, graphs::w_edge(1, 4));
}

TEST(KargerAlgo_FindCost, SmallExample_4) {
    auto example = examples::get_example(4);

    karger_algo algo(example.graph, example.spanningTree);
    algo.initialize();
    auto res = algo.find_cut();
    EXPECT_EQ(res.val, 28) << "found cut: " << res.e1 << ", " << res.e2;
}

TEST(KargerAlgo_FindCost, SmallExample_5) {
    auto example = examples::get_example(5);

    karger_algo algo(example.graph, example.spanningTree);
    algo.initialize();
    auto res = algo.find_cut();
    EXPECT_EQ(res.val, 17) << "found cut: " << res.e1 << ", " << res.e2;
}

TEST(KargerAlgo_FindCost, RandomSmallTest) {
    int testCases = 1000;
    int maxN = 50;
    int maxWeight = 40;

    utils::run_multiple_tests(testCases, maxN, maxWeight,
                              utils::test_find_cut_random_graph<karger_algo>);
}

TEST(KargerAlgo_FindCost, RandomMediumTest) {
    int testCases = 70;
    int maxN = 300;
    int maxWeight = 300;

    utils::run_multiple_tests(testCases, maxN, maxWeight,
                              utils::test_find_cut_random_graph<karger_algo>);
}

TEST(KargerAlgo_FindCost, RandomLargeTest) {
    int testCases = 5;
    int maxN = 1000;
    int maxWeight = 300;

    utils::run_multiple_tests(testCases, maxN, maxWeight,
                              utils::test_find_cut_random_graph<karger_algo>);
}
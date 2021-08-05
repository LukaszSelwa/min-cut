#include <gtest/gtest.h>

#include <limits>
#include <memory>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/main_algo/gmw_algo.hpp"
#include "../utils/brut_find_cut.hpp"

TEST(MainAlgo_FindCut, SmallExample_1) {
    auto example = examples::get_example(1);

    gmw_algo al(example.graph, example.spanningTree);
    al.initialize();
    auto res = al.find_cut();
    EXPECT_EQ(res.val, 4);
    EXPECT_EQ(res.e1, graphs::w_edge(6, 5));
    EXPECT_EQ(res.e2, graphs::w_edge(2, 1));
}

TEST(MainAlgo_FindCut, SmallExample_2) {
    auto example = examples::get_example(2);

    gmw_algo al(example.graph, example.spanningTree);
    al.initialize();
    auto res = al.find_cut();
    EXPECT_EQ(res.val, 1);
    EXPECT_EQ(res.e1, graphs::w_edge(1, 4));
    EXPECT_EQ(res.e2, graphs::w_edge(1, 4));
}

TEST(MainAlgo_FindCut, RandomSmallTest) {
    int testCases = 1000;
    int maxN = 50;
    int maxWeight = 40;

    utils::run_multiple_tests(testCases, maxN, maxWeight,
                              utils::test_find_cut_random_graph<gmw_algo>);
}

TEST(MainAlgo_FindCut, RandomMediumTest) {
    int testCases = 70;
    int maxN = 300;
    int maxWeight = 300;

    utils::run_multiple_tests(testCases, maxN, maxWeight,
                              utils::test_find_cut_random_graph<gmw_algo>);
}

TEST(MainAlgo_FindCut, RandomLargeTest) {
    int testCases = 5;
    int maxN = 1000;
    int maxWeight = 300;

    utils::run_multiple_tests(testCases, maxN, maxWeight,
                              utils::test_find_cut_random_graph<gmw_algo>);
}
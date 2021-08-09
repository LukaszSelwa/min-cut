#include <gtest/gtest.h>

#include <iostream>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graph_generation/edge_cases.hpp"
#include "../../../src/graph_generation/random_graph_generation.hpp"
#include "../../../src/main_algo/heuristic_algo.hpp"
#include "../../../src/naive_algo/naive_algo.hpp"
#include "../utils/run_tests.hpp"

bool test_min_cut_random_graph(int n, int maxWeight, std::mt19937 seed) {
    std::uniform_int_distribution<> dist(n - 1, n * (n - 1) / 2);
    auto sharedSeed = std::make_shared<std::mt19937>(seed);
    int m = dist(seed);
    auto graph = graphs::generate_random_graph(n, m, maxWeight, sharedSeed);

    naive::algo nAlgo(graph);
    heuristic::algo hAlgo(graph);
    auto resNaive = nAlgo.calc_min_cut();
    auto resHeuristic = hAlgo.calc_min_cut();

    EXPECT_EQ(resNaive.minCutVal, resHeuristic.minCutVal) << "test on graph " << *graph;
    return resNaive.minCutVal == resHeuristic.minCutVal;
}

TEST(NaiveVsHeuristic, RandomSmallTest) {
    int testCases = 100;
    int maxN = 50;
    int maxWeight = 20;

    std::random_device rd;
    std::mt19937 seed;
    std::uniform_int_distribution<> distN(1, maxN);

    utils::run_multiple_tests(
        testCases, [&]() { return test_min_cut_random_graph(distN(seed), maxWeight, seed); });
}

TEST(NaiveVsHeuristic, RandomMediumTest) {
    int testCases = 10;
    int maxN = 200;
    int maxWeight = 300;

    std::random_device rd;
    std::mt19937 seed;
    std::uniform_int_distribution<> distN(1, maxN);

    utils::run_multiple_tests(
        testCases, [&]() { return test_min_cut_random_graph(distN(seed), maxWeight, seed); });
}

TEST(NaiveVsHeuristic, RandomLargeTest) {
    int testCases = 2;
    int maxN = 400;
    int maxWeight = 400;

    std::random_device rd;
    std::mt19937 seed;
    std::uniform_int_distribution<> distN(1, maxN);

    utils::run_multiple_tests(
        testCases, [&]() { return test_min_cut_random_graph(distN(seed), maxWeight, seed); });
}

TEST(NaiveVsHeuristic, LadderGraph) {
    auto graph = generate_ladder_graph(100, 1000, 1);
    heuristic::algo hAlgo(graph);
    auto resHeuristic = hAlgo.calc_min_cut();

    EXPECT_EQ(resHeuristic.minCutVal, 100) << "test on ladder graph ";
}

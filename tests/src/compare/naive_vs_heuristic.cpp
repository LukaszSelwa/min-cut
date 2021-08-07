#include <gtest/gtest.h>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graphs/random_graph_generation.hpp"
#include "../../../src/main_algo/heuristic_algo.hpp"
#include "../../../src/naive_algo/naive_algo.hpp"

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
    int testCases = 200;
    int maxN = 50;
    int maxWeight = 20;

    std::random_device rd;
    std::mt19937 seed;
    std::uniform_int_distribution<> distN(1, maxN);

    while (testCases--) {
        if (!test_min_cut_random_graph(distN(seed), maxWeight, seed)) break;
    }
}

TEST(NaiveVsHeuristic, RandomMediumTest) {
    int testCases = 20;
    int maxN = 200;
    int maxWeight = 300;

    std::random_device rd;
    std::mt19937 seed;
    std::uniform_int_distribution<> distN(1, maxN);

    while (testCases--) {
        if (!test_min_cut_random_graph(distN(seed), maxWeight, seed)) break;
    }
}

TEST(NaiveVsHeuristic, RandomLargeTest) {
    int testCases = 1;
    int maxN = 400;
    int maxWeight = 400;

    std::random_device rd;
    std::mt19937 seed;
    std::uniform_int_distribution<> distN(1, maxN);

    while (testCases--) {
        if (!test_min_cut_random_graph(distN(seed), maxWeight, seed)) break;
    }
}
#include <gtest/gtest.h>

#include <iostream>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graph_generation/edge_cases.hpp"
#include "../../../src/graph_generation/random_graph_generation.hpp"
#include "../../../src/main_algo/heuristic_algo.hpp"
#include "../../../src/naive_algo/naive_algo.hpp"
#include "../utils/run_tests.hpp"

bool test_min_cut_random_graph(int n, int maxWeight, std::mt19937& seed) {
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

std::string get_cut_str(std::vector<bool>& cut) {
    std::stringstream ss;
    ss << "{";
    for (auto c : cut) ss << (c ? 1 : 0) << ", ";
    ss << "}";
    return ss.str();
}

bool test_min_cut_better_random_graph(size_t minSize, size_t maxSize, size_t maxCutVal,
                                      size_t minNSpanningTrees, size_t maxNrSpanningTrees,
                                      std::shared_ptr<std::mt19937> seed) {
    auto input = graphs::generate_fully_random_graph_input(
        minSize, maxSize, maxCutVal, minNSpanningTrees, maxNrSpanningTrees, seed);

    std::cout << " testing graph with size: " << input.graph->size << std::flush;
    heuristic::algo hAlgo(input.graph);
    auto resHeuristic = hAlgo.calc_min_cut();

    EXPECT_EQ(resHeuristic.minCutVal, input.minCutVal) << "test cut val on graph " << *input.graph;
    if (input.minCut.size() > 0) {
        bool validation = validate_cuts(input.minCut, resHeuristic.cut);
        EXPECT_TRUE(validation) << "test cut vector in graph " << *input.graph << " got cut "
                                << get_cut_str(resHeuristic.cut) << " but expected "
                                << get_cut_str(input.minCut);
        return validation && input.minCutVal == resHeuristic.minCutVal;
    }
    return input.minCutVal == resHeuristic.minCutVal;
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

TEST(NaiveVsHeuristic, BetterRandomSmallTest) {
    int testCases = 100;

    std::random_device rd;
    auto seed = std::make_shared<std::mt19937>();

    utils::run_multiple_tests(
        testCases, [&]() { return test_min_cut_better_random_graph(4, 64, 1100, 1, 4, seed); });
}

TEST(NaiveVsHeuristic, BetterRandomMediumTest) {
    int testCases = 10;

    std::random_device rd;
    auto seed = std::make_shared<std::mt19937>();

    utils::run_multiple_tests(
        testCases, [&]() { return test_min_cut_better_random_graph(64, 256, 20000, 1, 32, seed); });
}

TEST(NaiveVsHeuristic, BetterRandomLargeTest) {
    int testCases = 20;

    std::random_device rd;
    auto seed = std::make_shared<std::mt19937>();

    utils::run_multiple_tests(testCases, [&]() {
        return test_min_cut_better_random_graph(256, 384, 40000, 1, 64, seed);
    });
}
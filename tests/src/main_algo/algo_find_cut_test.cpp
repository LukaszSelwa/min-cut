#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <random>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graphs/random_graph_generation.hpp"
#include "../../../src/main_algo/algo.hpp"
#include "../../../src/spanning_trees_extractors/random_spanning_trees_extractor.hpp"

TEST(MainAlgo_FindCut, SmallExample_1) {
    auto example = examples::get_example(1);

    algo al(example.graph, example.spanningTree);
    al.initialize_structures();
    auto res = al.find_cut();
    EXPECT_EQ(res.val, 4);
    EXPECT_EQ(res.e1, graphs::w_edge(6, 5));
    EXPECT_EQ(res.e2, graphs::w_edge(2, 1));
}

TEST(MainAlgo_FindCut, SmallExample_2) {
    auto example = examples::get_example(2);

    algo al(example.graph, example.spanningTree);
    al.initialize_structures();
    auto res = al.find_cut();
    EXPECT_EQ(res.val, 1);
    EXPECT_EQ(res.e1, graphs::w_edge(1, 4));
    EXPECT_EQ(res.e2, graphs::w_edge(1, 4));
}

edge_pair brut_find_cut(std::shared_ptr<graphs::weighted_tree> tree,
                        std::shared_ptr<gmw_structure> gmw) {
    edge_pair result{.e1 = NIL_EDGE, .e2 = NIL_EDGE, .val = std::numeric_limits<int>::max()};
    for (auto& v1 : tree->vertices) {
        for (auto& v2 : tree->vertices) {
            if (v1.idx == tree->rootIdx || v2.idx == tree->rootIdx) continue;
            int val = gmw->get_cut_val(v1.parentEdge, v2.parentEdge);
            if (val < result.val)
                result = edge_pair{.e1 = v1.parentEdge, .e2 = v2.parentEdge, .val = val};
        }
    }
    return result;
}

void test_algo_find_cut(std::shared_ptr<graphs::weighted_graph> graph,
                        std::shared_ptr<graphs::weighted_tree> tree) {
    algo al(graph, tree);
    al.initialize_structures();
    auto gmw = al.gmw;
    auto res = al.find_cut();
    auto exp = brut_find_cut(tree, gmw);
    ASSERT_EQ(res.val, exp.val) << "should find minimum VALUE for graph: " << *graph
                                << " and spanning tree" << *tree;
    if (res.val != std::numeric_limits<int>::max())
        ASSERT_EQ(res.val, gmw->get_cut_val(res.e1, res.e2))
            << "should also find minimum CUT for graph: " << *graph << " and spanning tree"
            << *tree;
}

void test_algo_find_cut_random_graph(int n, int maxWeight, std::shared_ptr<std::mt19937> seed) {
    std::uniform_int_distribution<> dist(n - 1, n * (n - 1) / 2);
    int m = dist(*seed);
    auto graph = graphs::generate_random_graph(n, m, maxWeight, seed);
    std::shared_ptr<graphs::weighted_tree> tree(
        new graphs::weighted_tree(extractSingleRandomSpanningTree(*graph, seed)));

    test_algo_find_cut(graph, tree);
}

TEST(MainAlgo_FindCut, RandomSmallTest) {
    int testCases = 1000;
    int maxN = 50;
    int maxWeight = 40;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937(rd()));
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) test_algo_find_cut_random_graph(distN(*seed), maxWeight, seed);
}

TEST(MainAlgo_FindCut, RandomMediumTest) {
    int testCases = 70;
    int maxN = 300;
    int maxWeight = 300;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937());
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) test_algo_find_cut_random_graph(distN(*seed), maxWeight, seed);
}

TEST(MainAlgo_FindCut, RandomLargeTest) {
    int testCases = 5;
    int maxN = 1000;
    int maxWeight = 300;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937());
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) test_algo_find_cut_random_graph(distN(*seed), maxWeight, seed);
}
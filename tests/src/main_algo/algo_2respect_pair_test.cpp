#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <random>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graphs/random_graph_generation.hpp"
#include "../../../src/main_algo/gmw_algo.hpp"
#include "../../../src/spanning_trees_extractors/random_spanning_trees_extractor.hpp"

TEST(MainAlgo_2respectPair, SmallExample_1) {
    auto example = examples::get_example(1);

    gmw_algo al(example.graph, example.spanningTree);
    al.initialize();
    auto res = al.find_2respect_cut_pair(al.hld->interesting_pairs[0]);
    EXPECT_EQ(res.val, 11);
    EXPECT_EQ(res.e1, graphs::w_edge(5, 1));
    EXPECT_EQ(res.e2, graphs::w_edge(1, 0));

    res = al.find_2respect_cut_pair(al.hld->interesting_pairs[1]);
    EXPECT_EQ(res.val, 4);
    EXPECT_EQ(res.e1, graphs::w_edge(6, 5));
    EXPECT_EQ(res.e2, graphs::w_edge(2, 1));
}

edge_pair brut_find_2respect_cut_pair(graphs::interested_path_pair& ip,
                                      std::shared_ptr<gmw_structure> gmw) {
    edge_pair result{.e1 = NIL_EDGE, .e2 = NIL_EDGE, .val = std::numeric_limits<int>::max()};
    for (int i = 0; i < ip.edgesP.size(); ++i) {
        for (int j = 0; j < ip.edgesQ.size(); ++j) {
            int val = gmw->get_cut_val(ip.edgesP[i], ip.edgesQ[j]);
            if (val < result.val)
                result = edge_pair{.e1 = ip.edgesP[i], .e2 = ip.edgesQ[j], .val = val};
        }
    }
    return result;
}

void test_2respect_pair(std::shared_ptr<graphs::weighted_graph> graph,
                        std::shared_ptr<graphs::weighted_tree> tree) {
    gmw_algo al(graph, tree);
    al.initialize();
    auto gmw = al.gmw;
    auto hld = al.hld;
    for (auto& ip : al.hld->interesting_pairs) {
        auto res = al.find_2respect_cut_pair(ip);
        auto exp = brut_find_2respect_cut_pair(ip, gmw);
        ASSERT_EQ(res.val, exp.val)
            << "should find minimum VALUE for graph: " << *graph << " and spanning tree" << *tree;
        if (res.val != std::numeric_limits<int>::max())
            ASSERT_EQ(res.val, gmw->get_cut_val(res.e1, res.e2))
                << "should also find minimum CUT for graph: " << *graph << " and spanning tree"
                << *tree;
    }
}

void test_2respect_pair_random_graph(int n, int maxWeight, std::shared_ptr<std::mt19937> seed) {
    std::uniform_int_distribution<> dist(n - 1, n * (n - 1) / 2);
    int m = dist(*seed);
    auto graph = graphs::generate_random_graph(n, m, maxWeight, seed);
    std::shared_ptr<graphs::weighted_tree> tree(
        new graphs::weighted_tree(extractSingleRandomSpanningTree(*graph, seed)));

    test_2respect_pair(graph, tree);
}

TEST(MainAlgo_2respectPair, RandomSmallTest) {
    int testCases = 1000;
    int maxN = 50;
    int maxWeight = 40;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937(rd()));
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) test_2respect_pair_random_graph(distN(*seed), maxWeight, seed);
}

TEST(MainAlgo_2respectPair, RandomMediumTest) {
    int testCases = 100;
    int maxN = 300;
    int maxWeight = 300;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937());
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) test_2respect_pair_random_graph(distN(*seed), maxWeight, seed);
}

TEST(MainAlgo_2respectPair, RandomLargeTest) {
    int testCases = 10;
    int maxN = 1000;
    int maxWeight = 300;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937());
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) test_2respect_pair_random_graph(distN(*seed), maxWeight, seed);
}
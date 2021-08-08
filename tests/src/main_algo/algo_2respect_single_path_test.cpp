#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <random>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graph_generation/random_graph_generation.hpp"
#include "../../../src/main_algo/gmw_algo.hpp"
#include "../../../src/spanning_trees_extractors/random_spanning_trees_extractor.hpp"

TEST(MainAlgo_2respectSinglePath, SmallExample_1) {
    auto example = examples::get_example(1);

    gmw_algo al(example.graph, example.spanningTree);
    al.initialize();
    auto res = al.find_2respect_cut_single(0);
    EXPECT_EQ(res.val, 8);
    EXPECT_EQ(res.e1, graphs::w_edge(7, 3));
    EXPECT_EQ(res.e2, graphs::w_edge(3, 2));

    res = al.find_2respect_cut_single(1);
    EXPECT_EQ(res.val, 6);
    EXPECT_EQ(res.e1, graphs::w_edge(6, 5));
    EXPECT_EQ(res.e2, graphs::w_edge(5, 1));

    res = al.find_2respect_cut_single(2);
    EXPECT_EQ(res.val, std::numeric_limits<int>::max());
    EXPECT_EQ(res.e1, NIL_EDGE);
    EXPECT_EQ(res.e2, NIL_EDGE);
}

TEST(MainAlgo_2respectSinglePath, SmallExample_2) {
    auto example = examples::get_example(2);

    gmw_algo al(example.graph, example.spanningTree);
    al.initialize();
    auto res = al.find_2respect_cut_single(0);
    EXPECT_EQ(res.val, 1);
    EXPECT_EQ(res.e1, graphs::w_edge(1, 4));
    EXPECT_EQ(res.e2, graphs::w_edge(4, 9));

    res = al.find_2respect_cut_single(5);
    EXPECT_EQ(res.val, 18);
    EXPECT_EQ(res.e1, graphs::w_edge(2, 6));
    EXPECT_EQ(res.e2, graphs::w_edge(6, 0));
}

edge_pair brut_find_2respect_cut_in_single_hl_path(std::vector<graphs::w_edge> edges,
                                                   std::shared_ptr<gmw_structure> gmw) {
    edge_pair result{.e1 = NIL_EDGE, .e2 = NIL_EDGE, .val = std::numeric_limits<int>::max()};
    for (int i = 0; i < edges.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            int val = gmw->get_cut_val(edges[i], edges[j]);
            if (val < result.val) result = edge_pair{.e1 = edges[i], .e2 = edges[j], .val = val};
        }
    }
    return result;
}

void test_2respect_cut_in_single(std::shared_ptr<graphs::weighted_graph> graph,
                                 std::shared_ptr<graphs::weighted_tree> tree) {
    gmw_algo al(graph, tree);
    al.initialize();
    auto gmw = al.gmw;
    auto hld = al.hld;
    for (size_t i = 0; i < hld->paths.size(); ++i) {
        auto res = al.find_2respect_cut_single(i);
        auto exp = brut_find_2respect_cut_in_single_hl_path(hld->paths[i].edges, gmw);
        ASSERT_EQ(res.val, exp.val)
            << "should find minimum VALUE for graph: " << *graph << " and spanning tree" << *tree;
        if (res.val != std::numeric_limits<int>::max())
            ASSERT_EQ(res.val, gmw->get_cut_val(res.e1, res.e2))
                << "should also find minimum CUT for graph: " << *graph << " and spanning tree"
                << *tree;
    }
}

void test_2respect_random_graph(int n, int maxWeight, std::shared_ptr<std::mt19937> seed) {
    std::uniform_int_distribution<> dist(n - 1, n * (n - 1) / 2);
    int m = dist(*seed);
    auto graph = graphs::generate_random_graph(n, m, maxWeight, seed);
    std::shared_ptr<graphs::weighted_tree> tree(
        new graphs::weighted_tree(extractSingleRandomSpanningTree(*graph, seed)));

    test_2respect_cut_in_single(graph, tree);
}

TEST(MainAlgo_2respectSinglePath, RandomSmallTest) {
    int testCases = 1000;
    int maxN = 50;
    int maxWeight = 40;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937(rd()));
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) test_2respect_random_graph(distN(*seed), maxWeight, seed);
}

TEST(MainAlgo_2respectSinglePath, RandomMediumTest) {
    int testCases = 100;
    int maxN = 300;
    int maxWeight = 300;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937());
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) test_2respect_random_graph(distN(*seed), maxWeight, seed);
}

TEST(MainAlgo_2respectSinglePath, RandomLargeTest) {
    int testCases = 10;
    int maxN = 1000;
    int maxWeight = 300;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937());
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) test_2respect_random_graph(distN(*seed), maxWeight, seed);
}
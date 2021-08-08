#include "../../../src/graphs/hl_decomposition.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graph_generation/random_graph_generation.hpp"
#include "../../../src/range_search/segment_2d_point_tree.hpp"
#include "../../../src/spanning_trees_extractors/random_spanning_trees_extractor.hpp"

void test_is_every_interesting_pair(graphs::weighted_graph& graph, graphs::weighted_tree& tree,
                                    gmw_structure& gmw, graphs::hl_decomposition& hld) {
    size_t n = tree.size;
    std::vector<std::vector<bool>> found_interested(n, std::vector<bool>(n, false));
    for (auto& pair : hld.interesting_pairs) {
        for (auto& eP : pair.edgesP) {
            for (auto& eQ : pair.edgesQ)
                found_interested[eP.srcIdx][eQ.srcIdx] = found_interested[eQ.srcIdx][eP.srcIdx] =
                    true;
        }
    }

    for (auto& v1 : tree.vertices) {
        for (auto v2 : tree.vertices) {
            if (v1.idx == tree.rootIdx || v2.idx == tree.rootIdx || v1.hlPathId == v2.hlPathId)
                continue;
            if (gmw.is_crossinterested(v1.parentEdge, v2.parentEdge) &&
                gmw.is_crossinterested(v2.parentEdge, v1.parentEdge)) {
                ASSERT_TRUE(found_interested[v1.idx][v2.idx])
                    << "edges: " << v1.parentEdge << "; " << v2.parentEdge
                    << "are mutually CROSS-interested and should be included in interesting pairs "
                       "for graph:\n"
                    << graph << "\n and spanning tree: \n"
                    << tree;
            }
            if (gmw.is_downinterested(v1.parentEdge, v2.parentEdge) &&
                gmw.is_downinterested(v2.parentEdge, v1.parentEdge)) {
                ASSERT_TRUE(found_interested[v1.idx][v2.idx])
                    << "edges: " << v1.parentEdge << "; " << v2.parentEdge
                    << "are mutually DOWN-interested and should be included in interesting pairs "
                       "for graph:\n"
                    << graph << "\n and spanning tree: \n"
                    << tree;
            }
        }
    }
}

void test_number_of_interesting_pairs(graphs::weighted_graph& graph, graphs::weighted_tree& tree,
                                      graphs::hl_decomposition& hld) {
    size_t total_pairs = 0;
    for (auto& pair : hld.interesting_pairs) {
        total_pairs += pair.edgesP.size();
        total_pairs += pair.edgesQ.size();
    }
    size_t upper_bound = 2 * tree.size * (size_t)std::ceil((long double)tree.size);
    EXPECT_LE(total_pairs, upper_bound)
        << "number of interesting pairs should be less than " << upper_bound << "and is "
        << total_pairs << "for graph: \n"
        << graph << "and spanning tree: \n"
        << tree;
}

void calc_bottom_interested(std::shared_ptr<graphs::weighted_tree> tree,
                            std::shared_ptr<gmw_structure> gmw) {
    graphs::binarized_tree bTree(tree, gmw);
    bTree.initialize();
    for (auto& v : tree->vertices) {
        if (v.idx != tree->rootIdx) {
            v.bottomCrossinterested = bTree.find_bottom_crossinterested(v.parentEdge);
            v.bottomDowninterested = bTree.find_bottom_downinterested(v.parentEdge);
        }
    }
}

TEST(Graphs_HLDecomposition, Decompose_SmallTest_1) {
    auto e = examples::get_example(1);
    auto graph = e.graph;
    auto tree = e.spanningTree;

    graphs::hl_decomposition hld(tree);
    hld.decompose();
    std::vector<int> ctr(hld.paths.size(), 0);
    for (auto& v : tree->vertices) {
        if (v.idx != tree->rootIdx) ctr[v.hlPathId]++;
    }
    std::sort(ctr.begin(), ctr.end());
    std::vector<int> expCtr{1, 2, 4};
    EXPECT_EQ(ctr, expCtr);
}

TEST(Graphs_HLDecomposition, SmallTest_1) {
    auto e = examples::get_example(1);
    auto graph = e.graph;
    auto tree = e.spanningTree;
    std::shared_ptr<gmw_structure> gmw(
        new gmw_structure(std::make_unique<segment_2d_point_tree>(9)));
    gmw->initialize(graph, tree);
    calc_bottom_interested(tree, gmw);

    graphs::hl_decomposition hld(tree);
    hld.initialize(gmw);
    test_is_every_interesting_pair(*graph, *tree, *gmw, hld);
    test_number_of_interesting_pairs(*graph, *tree, hld);
}

TEST(Graphs_HLDecomposition, SmallTest_2) {
    auto e = examples::get_example(2);
    auto graph = e.graph;
    auto tree = e.spanningTree;
    std::shared_ptr<gmw_structure> gmw(
        new gmw_structure(std::make_unique<segment_2d_point_tree>(11)));
    gmw->initialize(graph, tree);
    calc_bottom_interested(tree, gmw);

    graphs::hl_decomposition hld(tree);
    hld.initialize(gmw);
    test_is_every_interesting_pair(*graph, *tree, *gmw, hld);
    test_number_of_interesting_pairs(*graph, *tree, hld);
}

TEST(Graphs_HLDecomposition, SmallTest_3) {
    auto e = examples::get_example(3);
    auto graph = e.graph;
    auto tree = e.spanningTree;
    std::shared_ptr<gmw_structure> gmw(
        new gmw_structure(std::make_unique<segment_2d_point_tree>(8)));
    gmw->initialize(graph, tree);
    calc_bottom_interested(tree, gmw);

    graphs::hl_decomposition hld(tree);
    hld.initialize(gmw);
    test_is_every_interesting_pair(*graph, *tree, *gmw, hld);
    test_number_of_interesting_pairs(*graph, *tree, hld);
}

void hld_test_random_graph(int n, int maxWeight, std::shared_ptr<std::mt19937> seed) {
    std::uniform_int_distribution<> dist(n - 1, n * (n - 1) / 2);
    int m = dist(*seed);
    auto graph = graphs::generate_random_graph(n, m, maxWeight, seed);
    std::shared_ptr<graphs::weighted_tree> tree(
        new graphs::weighted_tree(extractSingleRandomSpanningTree(*graph, seed)));

    std::shared_ptr<gmw_structure> gmw(
        new gmw_structure(std::make_unique<segment_2d_point_tree>(n + 1)));
    gmw->initialize(graph, tree);
    calc_bottom_interested(tree, gmw);
    graphs::hl_decomposition hld(tree);
    hld.initialize(gmw);

    test_is_every_interesting_pair(*graph, *tree, *gmw, hld);
    test_number_of_interesting_pairs(*graph, *tree, hld);
}

TEST(Graphs_HLDecomposition, HLDRandomTest) {
    int testCases = 50;
    int maxN = 50;
    int maxWeight = 10;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937(rd()));
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) hld_test_random_graph(distN(*seed), maxWeight, seed);
}

TEST(Graphs_HLDecomposition, HLDRandomLargeTest) {
    int testCases = 50;
    int maxN = 500;
    int maxWeight = 300;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937(rd()));
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) hld_test_random_graph(distN(*seed), maxWeight, seed);
}
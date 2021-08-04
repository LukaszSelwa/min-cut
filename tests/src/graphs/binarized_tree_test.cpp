#include "../../../src/graphs/binarized_tree.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <random>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graphs/gmw_structure.hpp"
#include "../../../src/graphs/random_graph_generation.hpp"
#include "../../../src/range_search/segment_2d_point_tree.hpp"
#include "../../../src/spanning_trees_extractors/random_spanning_trees_extractor.hpp"

void test_visited_all_nodes(std::shared_ptr<graphs::weighted_tree> tree,
                            graphs::binarized_tree& bTree) {
    std::vector<int> visit_ctr(tree->size, 0);
    std::vector<int> exp_visit_ctr(tree->size, 0);

    std::function<void(graphs::binarized_node*)> dfs = [&](graphs::binarized_node* nd) {
        visit_ctr[nd->orgIdx]++;
        if (nd->left != nullptr) dfs(nd->left);
        if (nd->right != nullptr) dfs(nd->right);
    };
    dfs(&bTree.vertices[0]);
    for (auto& v : tree->vertices) exp_visit_ctr[v.idx] = std::max(1, (int)v.children.size());
    EXPECT_EQ(visit_ctr, exp_visit_ctr);
}

void test_visited_all_centroids(std::shared_ptr<graphs::weighted_tree> tree,
                                graphs::binarized_tree& bTree) {
    std::vector<int> visit_ctr(tree->size, 0);
    std::vector<int> exp_visit_ctr(tree->size, 0);

    std::function<void(graphs::centroid*)> dfs = [&](graphs::centroid* c) {
        visit_ctr[c->bNode->orgIdx]++;
        if (c->top != nullptr) dfs(c->top);
        if (c->left != nullptr) dfs(c->left);
        if (c->right != nullptr) dfs(c->right);
    };
    dfs(&bTree.centroids[0]);
    for (auto& v : tree->vertices) exp_visit_ctr[v.idx] = std::max(1, (int)v.children.size());
    EXPECT_EQ(visit_ctr, exp_visit_ctr);
}

void test_centroids_size(std::shared_ptr<graphs::weighted_tree> tree,
                         graphs::binarized_tree& bTree) {
    std::function<int(graphs::centroid*)> dfs = [&](graphs::centroid* c) -> int {
        int sizes[3] = {0, 0, 0};
        if (c->top != nullptr) sizes[0] = dfs(c->top);
        if (c->left != nullptr) sizes[1] = dfs(c->left);
        if (c->right != nullptr) sizes[2] = dfs(c->right);
        int size = sizes[0] + sizes[1] + sizes[2];
        for (int i = 0; i < 3; ++i) EXPECT_TRUE(sizes[i] <= size / 2);
        return size;
    };
}

int find_bottom_interested(graphs::w_edge ed, std::shared_ptr<graphs::weighted_tree> tree,
                           std::function<bool(graphs::w_edge, graphs::w_edge)> is_interested) {
    std::function<int(int)> search = [&](int idx) -> int {
        for (auto& ed2 : tree->vertices[idx].children) {
            if (is_interested(ed, ed2)) return search(ed2.destIdx);
        }
        return idx;
    };
    return search(tree->rootIdx);
}

void test_crossinterested_points(graphs::binarized_tree& bTree,
                                 std::shared_ptr<graphs::weighted_tree> tree,
                                 std::shared_ptr<graphs::weighted_graph> graph,
                                 std::shared_ptr<gmw_structure> gmw) {
    auto is_crossinterested = [&](graphs::w_edge e1, graphs::w_edge e2) -> bool {
        return gmw->is_crossinterested(e1, e2);
    };
    for (auto& v : tree->vertices) {
        if (v.idx == tree->rootIdx) continue;
        ASSERT_EQ(bTree.find_bottom_crossinterested(v.parentEdge),
                  find_bottom_interested(v.parentEdge, tree, is_crossinterested))
            << "  Should find crossinterested point for edge: " << v.parentEdge
            << "\n  in spanning tree: " << *tree << "\n   for " << *graph;
    }
}

void test_downinterested_points(graphs::binarized_tree& bTree,
                                std::shared_ptr<graphs::weighted_tree> tree,
                                std::shared_ptr<graphs::weighted_graph> graph,
                                std::shared_ptr<gmw_structure> gmw) {
    auto is_downinterested = [&](graphs::w_edge e1, graphs::w_edge e2) -> bool {
        return gmw->is_downinterested(e1, e2);
    };
    for (auto& v : tree->vertices) {
        if (v.idx == tree->rootIdx) continue;
        ASSERT_EQ(bTree.find_bottom_downinterested(v.parentEdge),
                  find_bottom_interested(v.parentEdge, tree, is_downinterested))
            << "  Should find downinterested point for edge: " << v.parentEdge
            << "\n  in spanning tree: " << *tree << "\n   for " << *graph;
    }
}

TEST(Graphs_BinarizedTree, InitializeSmallTest_1) {
    auto e = examples::get_example(1);
    auto graph = e.graph;
    auto tree = e.spanningTree;
    std::shared_ptr<gmw_structure> gmw(
        new gmw_structure(std::make_unique<segment_2d_point_tree>(9)));
    gmw->initialize(graph, tree);

    graphs::binarized_tree bTree(tree, gmw);
    bTree.initialize();
    test_visited_all_nodes(tree, bTree);
    test_visited_all_centroids(tree, bTree);
    test_centroids_size(tree, bTree);
}

TEST(Graphs_BinarizedTree, InitializeSmallTest_2) {
    auto e = examples::get_example(2);
    auto graph = e.graph;
    auto tree = e.spanningTree;
    std::shared_ptr<gmw_structure> gmw(
        new gmw_structure(std::make_unique<segment_2d_point_tree>(10)));
    gmw->initialize(graph, tree);

    graphs::binarized_tree bTree(tree, gmw);
    bTree.initialize();
    test_visited_all_nodes(tree, bTree);
    test_visited_all_centroids(tree, bTree);
    test_centroids_size(tree, bTree);
}

TEST(Graphs_BinarizedTree, CrossinterestedSmallTest_1) {
    auto e = examples::get_example(1);
    auto graph = e.graph;
    auto tree = e.spanningTree;
    std::shared_ptr<gmw_structure> gmw(
        new gmw_structure(std::make_unique<segment_2d_point_tree>(9)));
    gmw->initialize(graph, tree);

    graphs::binarized_tree bTree(tree, gmw);
    bTree.initialize();

    std::vector<graphs::w_edge> edges{
        graphs::w_edge(3, 7), graphs::w_edge(2, 3), graphs::w_edge(1, 2), graphs::w_edge(0, 1),
        graphs::w_edge(1, 5), graphs::w_edge(5, 6), graphs::w_edge(0, 4),
    };
    std::vector<int> expCrossinterested{6, 6, 6, 4, 2, 3, 0};
    std::vector<int> corossinterested;
    for (auto& ed : edges) corossinterested.push_back(bTree.find_bottom_crossinterested(ed));
    EXPECT_EQ(corossinterested, expCrossinterested);
    test_crossinterested_points(bTree, tree, graph, gmw);
}

TEST(Graphs_BinarizedTree, CrossinterestedSmallTest_2) {
    auto e = examples::get_example(2);
    auto graph = e.graph;
    auto tree = e.spanningTree;
    std::shared_ptr<gmw_structure> gmw(
        new gmw_structure(std::make_unique<segment_2d_point_tree>(9)));
    gmw->initialize(graph, tree);

    graphs::binarized_tree bTree(tree, gmw);
    bTree.initialize();

    test_crossinterested_points(bTree, tree, graph, gmw);
}

TEST(Graphs_BinarizedTree, CrossinterestedSmallTest_3) {
    auto e = examples::get_example(3);
    auto graph = e.graph;
    auto tree = e.spanningTree;
    std::shared_ptr<gmw_structure> gmw(
        new gmw_structure(std::make_unique<segment_2d_point_tree>(9)));
    gmw->initialize(graph, tree);

    graphs::binarized_tree bTree(tree, gmw);
    bTree.initialize();

    EXPECT_EQ(bTree.find_bottom_crossinterested(graphs::w_edge(5, 6)), 5);
}

void test_b_tree_random_graph(int n, int maxWeight, std::shared_ptr<std::mt19937> seed) {
    std::uniform_int_distribution<> dist(n - 1, n * (n - 1) / 2);
    int m = dist(*seed);
    auto graph = graphs::generate_random_graph(n, m, maxWeight, seed);
    std::shared_ptr<graphs::weighted_tree> tree(
        new graphs::weighted_tree(extractSingleRandomSpanningTree(*graph, seed)));

    std::shared_ptr<gmw_structure> gmw(
        new gmw_structure(std::make_unique<segment_2d_point_tree>(n + 1)));
    gmw->initialize(graph, tree);
    graphs::binarized_tree bTree(tree, gmw);
    bTree.initialize();

    test_visited_all_centroids(tree, bTree);
    test_crossinterested_points(bTree, tree, graph, gmw);
    test_downinterested_points(bTree, tree, graph, gmw);
}

TEST(Graphs_BinarizedTree, RandomSmallTest) {
    int testCases = 1000;
    int maxN = 50;
    int maxWeight = 40;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937(rd()));
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) test_b_tree_random_graph(distN(*seed), maxWeight, seed);
}

TEST(Graphs_BinarizedTree, RandomLargeTest) {
    int testCases = 10;
    int maxN = 1000;
    int maxWeight = 300;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937());
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) test_b_tree_random_graph(distN(*seed), maxWeight, seed);
}

TEST(Graphs_BinarizedTree, DowninterestedSmallTest_1) {
    auto e = examples::get_example(1);
    auto graph = e.graph;
    auto tree = e.spanningTree;
    std::shared_ptr<gmw_structure> gmw(
        new gmw_structure(std::make_unique<segment_2d_point_tree>(9)));
    gmw->initialize(graph, tree);

    graphs::binarized_tree bTree(tree, gmw);
    bTree.initialize();

    std::vector<graphs::w_edge> edges{
        graphs::w_edge(3, 7), graphs::w_edge(2, 3), graphs::w_edge(1, 2), graphs::w_edge(0, 1),
        graphs::w_edge(1, 5), graphs::w_edge(5, 6), graphs::w_edge(0, 4),
    };
    std::vector<int> expDowninterested{7, 3, 2, 5, 6, 6, 4};
    std::vector<int> downinterested;
    for (auto& ed : edges) downinterested.push_back(bTree.find_bottom_downinterested(ed));
    EXPECT_EQ(downinterested, expDowninterested);
    test_downinterested_points(bTree, tree, graph, gmw);
}
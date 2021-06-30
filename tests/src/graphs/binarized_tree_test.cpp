#include <gtest/gtest.h>
#include <algorithm>
#include <functional>
#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graphs/binarized_tree.hpp"
#include "../../../src/graphs/gmw_structure.hpp"
#include "../../../src/range_search/interval2D_tree.hpp"


void test_visited_all_nodes(std::shared_ptr<graphs::WeightedTree> tree, graphs::binarized_tree & bTree) {
    std::vector<int> visit_ctr(tree->size, 0);
    std::vector<int> exp_visit_ctr(tree->size, 0);

    std::function<void(graphs::binarized_node*)> dfs = [&](graphs::binarized_node *nd) {
        visit_ctr[nd->orgIdx]++;
        if (nd->left != nullptr)
            dfs(nd->left);
        if (nd->right != nullptr)
            dfs(nd->right);
    };
    dfs(&bTree.vertices[0]);
    for (auto & v : tree->vertices)
        exp_visit_ctr[v.idx] = std::max(1, (int)v.children.size());
    EXPECT_EQ(visit_ctr, exp_visit_ctr);
}

void test_visited_all_centroids(std::shared_ptr<graphs::WeightedTree> tree, graphs::binarized_tree & bTree) {
    std::vector<int> visit_ctr(tree->size, 0);
    std::vector<int> exp_visit_ctr(tree->size, 0);

    std::function<void(graphs::centroid*)> dfs = [&](graphs::centroid *c) {
        visit_ctr[c->bNode->orgIdx]++;
        if (c->top != nullptr)
            dfs(c->top);
        if (c->left != nullptr)
            dfs(c->left);
        if (c->right != nullptr)
            dfs(c->right);
    };
    dfs(&bTree.centroids[0]);
    for (auto & v : tree->vertices)
        exp_visit_ctr[v.idx] = std::max(1, (int)v.children.size());
    EXPECT_EQ(visit_ctr, exp_visit_ctr);
}

void test_centroids_size(std::shared_ptr<graphs::WeightedTree> tree, graphs::binarized_tree & bTree) {
    std::function<int(graphs::centroid*)> dfs = [&](graphs::centroid *c)->int {
        int sizes[3] = {0, 0, 0};
        if (c->top != nullptr)
            sizes[0] = dfs(c->top);
        if (c->left != nullptr)
            sizes[1] = dfs(c->left);
        if (c->right != nullptr)
            sizes[2] = dfs(c->right);
        int size = sizes[0] + sizes[1] + sizes[2];
        for (int i = 0; i < 3; ++i)
            EXPECT_TRUE(sizes[i] <= size / 2);
        return size;
    };
}

TEST(Graphs_BinarizedTree, InitializeSmallTest_1) {
    auto e = examples::get_example(1);
    auto graph = e.graph;
    auto tree = e.spanningTree;
    std::shared_ptr<gmw_structure> gmw(new gmw_structure(std::make_unique<Interval2DTree>(9, 9)));
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
    std::shared_ptr<gmw_structure> gmw(new gmw_structure(std::make_unique<Interval2DTree>(10, 10)));
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
    std::shared_ptr<gmw_structure> gmw(new gmw_structure(std::make_unique<Interval2DTree>(9, 9)));
    gmw->initialize(graph, tree);

    graphs::binarized_tree bTree(tree, gmw);
    bTree.initialize();

    std::vector<graphs::WeightedEdge> edges{
        graphs::WeightedEdge(3,7),
        graphs::WeightedEdge(2,3),
        graphs::WeightedEdge(1,2),
        graphs::WeightedEdge(0,1),
        graphs::WeightedEdge(1,5),
        graphs::WeightedEdge(5,6),
        graphs::WeightedEdge(0,4),
    };
    std::vector<int> expCrossinterested{6, 6, 6, 7, 2, 3, 0};
    std::vector<int> corossinterested;
    for (auto & ed : edges)
        corossinterested.push_back(bTree.find_bottom_crossinterested(ed));
    EXPECT_EQ(corossinterested, expCrossinterested);
}
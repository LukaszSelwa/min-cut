#include <gtest/gtest.h>
#include <algorithm>
#include <functional>
#include "../../../src/graphs/binarized_tree.hpp"

void test_visited_all_nodes(std::shared_ptr<graphs::WeightedTree> tree, graphs::binarized_tree & bTree) {
    std::vector<int> visit_ctr(tree->size, 0);
    std::vector<int> exp_visit_ctr(tree->size, 0);

    std::function<void(int)> dfs = [&](int idx) {
        auto & v = bTree.vertices[idx];
        visit_ctr[v.orgIdx]++;
        if (v.children[0] != -1)
            dfs(v.children[0]);
        if (v.children[1] != -1)
            dfs(v.children[1]);
    };
    dfs(0);
    for (auto & v : tree->vertices)
        exp_visit_ctr[v.idx] = std::max(1, (int)v.children.size());
    EXPECT_EQ(visit_ctr, exp_visit_ctr);
}


TEST(Graphs_BinarizedTree, InitializeSmallTest_1) {
    std::shared_ptr<graphs::WeightedTree> tree(new graphs::WeightedTree(8));
    tree->AddChildEdge(0, 1, 2);
    tree->AddChildEdge(0, 4, 3);
    tree->AddChildEdge(1, 2, 3);
    tree->AddChildEdge(1, 5, 2);
    tree->AddChildEdge(2, 3, 4);
    tree->AddChildEdge(3, 7, 2);
    tree->AddChildEdge(5, 6, 1);

    graphs::binarized_tree bTree(tree);
    bTree.initialize();
    test_visited_all_nodes(tree, bTree);
}
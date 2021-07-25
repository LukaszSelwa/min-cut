#include "../../../src/graphs/weighted_tree.hpp"

#include <gtest/gtest.h>

TEST(Graphs_WeightedTree, PreOrderTest) {
    graphs::weighted_tree tree(3);
    tree.add_child_edge(0, 1, 1);
    tree.add_child_edge(1, 2, 1);

    std::vector<int> preorder(0);
    std::vector<int> parents(3);
    std::function<void(graphs::tree_vertice&)> markNodes = [&](graphs::tree_vertice& v) -> void {
        preorder.push_back(v.idx);
        parents[v.idx] = v.parentEdge.destIdx;
    };
    tree.run_preorder(markNodes);
    std::vector<int> expected{0, 1, 2};
    std::vector<int> expParents{-1, 0, 1};
    ASSERT_EQ(preorder, expected) << "Should visit path from 0 to 2";
    ASSERT_EQ(parents, expParents);
}

TEST(Graphs_WeightedTree, PostOrderTest) {
    graphs::weighted_tree tree(3);
    tree.add_child_edge(0, 1, 1);
    tree.add_child_edge(1, 2, 1);

    std::vector<int> postorder(0);
    std::vector<int> parents(3);
    std::function<void(graphs::tree_vertice&)> markNodes = [&](graphs::tree_vertice& v) -> void {
        postorder.push_back(v.idx);
        parents[v.idx] = v.parentEdge.destIdx;
    };
    tree.run_postorder(markNodes);
    std::vector<int> expected{2, 1, 0};
    std::vector<int> exp_parents{-1, 0, 1};
    EXPECT_EQ(postorder, expected) << "Should visit in post order";
    EXPECT_EQ(parents, exp_parents);
}
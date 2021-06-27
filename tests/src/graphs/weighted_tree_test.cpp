#include <gtest/gtest.h>
#include "../../../src/graphs/weighted_tree.hpp"

TEST(Graphs_WeightedTree, PreOrderTest) {
    graphs::WeightedTree tree(3);
    tree.AddEdge(0, 1, 1);
    tree.AddEdge(1, 2, 1);

    std::vector<int> preorder(0);
    std::vector<int> parents(3);
    tree.RunPreOrder([&](graphs::Vertice& v, int p_idx){
        preorder.push_back(v.GetIdx());
        parents[v.GetIdx()] = p_idx;
    });
    std::vector<int> expected{0, 1, 2};
    std::vector<int> exp_parents{-1, 0, 1};
    ASSERT_EQ(preorder, expected) << "Should visit path from 0 to 2";
    ASSERT_EQ(parents, exp_parents);
}

TEST(Graphs_WeightedTree, PostOrderTest) {
    graphs::WeightedTree tree(3);
    tree.AddEdge(0, 1, 1);
    tree.AddEdge(1, 2, 1);

    std::vector<int> postorder(0);
    std::vector<int> parents(3);
    tree.RunPostOrder([&](graphs::Vertice& v, int p_idx){
        postorder.push_back(v.GetIdx());
        parents[v.GetIdx()] = p_idx;
    });
    std::vector<int> expected{2, 1, 0};
    std::vector<int> exp_parents{-1, 0, 1};
    EXPECT_EQ(postorder, expected) << "Should visit in post order";
    EXPECT_EQ(parents, exp_parents);
}
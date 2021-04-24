#include <gtest/gtest.h>
#include "../../../src/graphs/weighted_tree.hpp"

TEST(Graphs_WeightedTree, PreOrderTest) {
    graphs::WeightedTree tree(3);
    tree.AddEdge(0, 1, 1);
    tree.AddEdge(1, 2, 1);

    std::vector<int> preorder(0);
    tree.RunPreOrder([&](graphs::Vertice& v){
        preorder.push_back(v.GetIdx());
    });
    std::vector<int> expected{0, 1, 2};
    EXPECT_EQ(preorder, expected) << "Should visit path from 0 to 2";
}
#include <gtest/gtest.h>
#include <memory>
#include "../../../src/graphs/lca_computer.hpp"

TEST(Graphs_LCAComputer, SmallTreeTest) {
    std::shared_ptr<graphs::WeightedTree> tree = std::make_shared<graphs::WeightedTree>(3);
    tree->AddEdge(0, 1, 1);
    tree->AddEdge(0, 2, 1);

    graphs::LCAComputer computer(tree);
    computer.Initialize();

    for (int i = 0; i < 3; ++i)
        EXPECT_EQ(computer.LCA(i, i), i) << "lca in single element";

    EXPECT_EQ(computer.LCA(1, 2), 0) << "lca in root";
    EXPECT_EQ(computer.LCA(2, 1), 0) << "lca in root";
    EXPECT_EQ(computer.LCA(0, 2), 0) << "lca in root";
    EXPECT_EQ(computer.LCA(2, 0), 0) << "lca in root";
    EXPECT_EQ(computer.LCA(0, 1), 0) << "lca in root";
    EXPECT_EQ(computer.LCA(1, 0), 0) << "lca in root";
}

TEST(Graphs_LCAComputer, Medium_Test) {
    std::shared_ptr<graphs::WeightedTree> tree(new graphs::WeightedTree(8));
    tree->AddEdge(0, 1, 2);
    tree->AddEdge(0, 4, 3);
    tree->AddEdge(1, 2, 3);
    tree->AddEdge(1, 5, 2);
    tree->AddEdge(2, 3, 4);
    tree->AddEdge(3, 7, 2);
    tree->AddEdge(5, 6, 1);

    graphs::LCAComputer computer(tree);
    computer.Initialize();

    for (int i = 0; i < 8; ++i)
        EXPECT_EQ(computer.LCA(i, i), i) << "lca in single element";
}
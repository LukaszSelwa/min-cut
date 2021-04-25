#include <gtest/gtest.h>
#include "../../../src/graphs/lca_computer.hpp"

TEST(Graphs_LCAComputer, SmallTreeTest) {
    graphs::WeightedTree tree(3);
    tree.AddEdge(0, 1, 1);
    tree.AddEdge(0, 2, 1);

    graphs::LCAComputer computer(&tree);
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
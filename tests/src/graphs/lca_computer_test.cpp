#include <gtest/gtest.h>
#include <memory>
#include "../../../src/graphs/lca_computer.hpp"

TEST(Graphs_LCAComputer, SmallTreeTest) {
    std::shared_ptr<graphs::WeightedTree> tree = std::make_shared<graphs::WeightedTree>(3);
    tree->AddChildEdge(0, 1, 1);
    tree->AddChildEdge(0, 2, 1);

    graphs::lca_computer computer(tree);
    computer.initialize();

    for (int i = 0; i < 3; ++i)
        EXPECT_EQ(computer.calc_lca(i, i), i) << "lca in single element";

    EXPECT_EQ(computer.calc_lca(1, 2), 0) << "lca in root";
    EXPECT_EQ(computer.calc_lca(2, 1), 0) << "lca in root";
    EXPECT_EQ(computer.calc_lca(0, 2), 0) << "lca in root";
    EXPECT_EQ(computer.calc_lca(2, 0), 0) << "lca in root";
    EXPECT_EQ(computer.calc_lca(0, 1), 0) << "lca in root";
    EXPECT_EQ(computer.calc_lca(1, 0), 0) << "lca in root";
}

TEST(Graphs_LCAComputer, Medium_Test) {
    std::shared_ptr<graphs::WeightedTree> tree(new graphs::WeightedTree(8));
    tree->AddChildEdge(0, 1, 2);
    tree->AddChildEdge(0, 4, 3);
    tree->AddChildEdge(1, 2, 3);
    tree->AddChildEdge(1, 5, 2);
    tree->AddChildEdge(2, 3, 4);
    tree->AddChildEdge(3, 7, 2);
    tree->AddChildEdge(5, 6, 1);

    graphs::lca_computer computer(tree);
    computer.initialize();

    for (int i = 0; i < 8; ++i)
        EXPECT_EQ(computer.calc_lca(i, i), i) << "lca in single element";
}
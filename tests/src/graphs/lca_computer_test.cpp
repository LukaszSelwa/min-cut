#include "../../../src/graphs/lca_computer.hpp"

#include <gtest/gtest.h>

#include <memory>

TEST(Graphs_LCAComputer, SmallTreeTest) {
    std::shared_ptr<graphs::weighted_tree> tree = std::make_shared<graphs::weighted_tree>(3);
    tree->add_child_edge(0, 1, 1);
    tree->add_child_edge(0, 2, 1);

    graphs::lca_computer computer(tree);
    computer.initialize();

    for (int i = 0; i < 3; ++i) EXPECT_EQ(computer.calc_lca(i, i), i) << "lca in single element";

    EXPECT_EQ(computer.calc_lca(1, 2), 0) << "lca in root";
    EXPECT_EQ(computer.calc_lca(2, 1), 0) << "lca in root";
    EXPECT_EQ(computer.calc_lca(0, 2), 0) << "lca in root";
    EXPECT_EQ(computer.calc_lca(2, 0), 0) << "lca in root";
    EXPECT_EQ(computer.calc_lca(0, 1), 0) << "lca in root";
    EXPECT_EQ(computer.calc_lca(1, 0), 0) << "lca in root";
}

TEST(Graphs_LCAComputer, Medium_Test) {
    std::shared_ptr<graphs::weighted_tree> tree(new graphs::weighted_tree(8));
    tree->add_child_edge(0, 1, 2);
    tree->add_child_edge(0, 4, 3);
    tree->add_child_edge(1, 2, 3);
    tree->add_child_edge(1, 5, 2);
    tree->add_child_edge(2, 3, 4);
    tree->add_child_edge(3, 7, 2);
    tree->add_child_edge(5, 6, 1);

    graphs::lca_computer computer(tree);
    computer.initialize();

    for (int i = 0; i < 8; ++i) EXPECT_EQ(computer.calc_lca(i, i), i) << "lca in single element";
}
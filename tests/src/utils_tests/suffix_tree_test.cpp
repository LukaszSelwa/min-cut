#include "../../../src/utils/suffix_tree.hpp"

#include <gtest/gtest.h>

TEST(Utils_PrefixTree, EmptyTest) {
    suffix_tree tree(2);

    EXPECT_EQ(tree.first_geq_idx(0), 0);
    EXPECT_EQ(tree.first_geq_idx(1), 1);
}

TEST(Utils_PrefixTree, SmallExample_1) {
    suffix_tree tree(6);
    tree.add_to_suffix(0, 1);
    tree.add_to_suffix(1, 1);
    tree.add_to_suffix(2, 1);
    tree.add_to_suffix(3, 1);
    tree.add_to_suffix(4, 1);
    tree.add_to_suffix(5, 1);

    EXPECT_EQ(tree.first_geq_idx(1), 0);
    EXPECT_EQ(tree.first_geq_idx(2), 1);
    EXPECT_EQ(tree.first_geq_idx(3), 2);
    EXPECT_EQ(tree.first_geq_idx(4), 3);
    EXPECT_EQ(tree.first_geq_idx(5), 4);
    EXPECT_EQ(tree.first_geq_idx(6), 5);
}
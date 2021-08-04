#include "../../../src/range_search/interval_tree.hpp"

#include <gtest/gtest.h>

TEST(RangeSearch_IntervalTree, Test0TreeSize) {
    interval_tree tree;
    EXPECT_EQ(tree.get_size(), 0) << "Tree had size 0";
}

TEST(RangeSearch_IntervalTree, TestTreeSize) {
    interval_tree tree(10);
    EXPECT_EQ(tree.get_size(), 10) << "Tree had size 10";
}

TEST(RangeSearch_IntervalTree, TestEmptyTree) {
    interval_tree tree(10);
    EXPECT_EQ(tree.sum(0, 9), 0) << "No elements where added";
    EXPECT_EQ(tree.sum(0, 5), 0) << "No elements where added";
    EXPECT_EQ(tree.sum(1, 1), 0) << "No elements where added";
}

TEST(RangeSearch_IntervalTree, TestAddPoint) {
    interval_tree tree(10);
    tree.add_point(1, 2);
    tree.add_point(3, 1);
    tree.add_point(3, 1);
    EXPECT_EQ(tree.sum(1, 1), 2) << "Added once 2 to index 1";
    EXPECT_EQ(tree.sum(3, 3), 2) << "Added twice 1 to index 3";
    EXPECT_EQ(tree.sum(2, 2), 0) << "Not added anything to index 2";
    EXPECT_EQ(tree.sum(1, 3), 4) << "Added 4 on range [1, 3]";
}

TEST(RangeSearch_IntervalTree, TestSetPoint) {
    interval_tree tree(10);
    tree.set_point(1, 2);
    tree.set_point(3, 1);
    tree.set_point(3, 1);
    EXPECT_EQ(tree.sum(1, 1), 2) << "Set index 1 to 2";
    EXPECT_EQ(tree.sum(3, 3), 1) << "Set index 3 to 1";
    EXPECT_EQ(tree.sum(2, 2), 0) << "Didn't set index 2";
    EXPECT_EQ(tree.sum(1, 3), 3) << "Range [1, 3] should have sum 3";
}

TEST(RangeSearch_IntervalTree, TestPointVal) {
    interval_tree tree(10);
    tree.set_point(1, 2);
    tree.set_point(3, 1);
    tree.set_point(3, 1);
    EXPECT_EQ(tree.get_point(1), 2) << "Set index 1 to 2";
    EXPECT_EQ(tree.get_point(2), 0) << "Didn't set index 2";
    EXPECT_EQ(tree.get_point(3), 1) << "Set index 3 to 1";
}
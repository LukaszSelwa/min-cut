#include <gtest/gtest.h>
#include <memory>
#include "../../../src/range_search/interval_tree.hpp"

TEST(RangeSearch_IntervalTree, TestTreeSize) {
    IntervalTree tree(10);
    EXPECT_EQ(tree.GetSize(), 10) << "Tree had size 10";
}

TEST(RangeSearch_IntervalTree, TestEmptyTree) {
    IntervalTree tree(10);
    EXPECT_EQ(tree.SumInRange(0, 9), 0) << "No elements where added";
    EXPECT_EQ(tree.SumInRange(0, 5), 0) << "No elements where added";
    EXPECT_EQ(tree.SumInRange(1, 1), 0) << "No elements where added";
}

TEST(RangeSearch_IntervalTree, TestAddPoint) {
    IntervalTree tree(10);
    tree.AddPoint(1, 2);
    tree.AddPoint(3, 1);
    tree.AddPoint(3, 1);
    EXPECT_EQ(tree.SumInRange(1, 1), 2) << "Added once 2 to index 1";
    EXPECT_EQ(tree.SumInRange(3, 3), 2) << "Added twice 1 to index 3";
    EXPECT_EQ(tree.SumInRange(2, 2), 0) << "Not added anything to index 2";
    EXPECT_EQ(tree.SumInRange(1, 3), 4) << "Added 4 on range [1, 3]";
}

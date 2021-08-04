#include "../../../src/range_search/interval_point.hpp"

#include <gtest/gtest.h>

TEST(RangeSearch_PointerIntervalTree, TestEmptyTree) {
    interval_point<1, int> point(10);
    EXPECT_EQ(point.get_sum(0, 9), 0) << "No elements where added";
    EXPECT_EQ(point.get_sum(0, 5), 0) << "No elements where added";
    EXPECT_EQ(point.get_sum(1, 1), 0) << "No elements where added";
}

TEST(RangeSearch_PointerIntervalTree, TestAddPoint) {
    interval_point<1, int> point(10);
    point.add_point(2, 1);
    point.add_point(1, 3);
    point.add_point(1, 3);
    EXPECT_EQ(point.get_sum(1, 1), 2) << "Added once 2 to index 1";
    EXPECT_EQ(point.get_sum(3, 3), 2) << "Added twice 1 to index 3";
    EXPECT_EQ(point.get_sum(2, 2), 0) << "Not added anything to index 2";
    EXPECT_EQ(point.get_sum(1, 3), 4) << "Added 4 on range [1, 3]";
}

TEST(RangeSearch_PointerIntervalTree, GetSumInRectangleEmptyTest) {
    interval_point<2, int> point(16);
    EXPECT_EQ(point.get_sum(0, 9, 0, 15), 0) << "Rectangle should be empty";
    EXPECT_EQ(point.get_sum(2, 3, 11, 13), 0) << "Rectangle should be empty";
}

TEST(RangeSearch_PointerIntervalTree, GetSumInRectangleTest) {
    interval_point<2, int> point(16);
    point.add_point(1, 1, 2);
    point.add_point(1, 1, 2);
    point.add_point(10, 9, 5);
    EXPECT_EQ(point.get_sum(2, 2, 3, 3), 0) << "Point (2, 3) should be empty";
    EXPECT_EQ(point.get_sum(1, 1, 2, 2), 2) << "Point (1, 2) should have value 2";
    EXPECT_EQ(point.get_sum(9, 9, 5, 5), 10) << "Point (9, 5) should be empty";
    EXPECT_EQ(point.get_sum(1, 9, 1, 8), 12) << "Rectangle [1,9]x[1, 8] should have value 12";
}
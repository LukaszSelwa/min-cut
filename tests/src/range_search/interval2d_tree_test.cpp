#include "../../../src/range_search/interval2D_tree.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <random>
#include <vector>

#include "../../../src/range_search/range_search_structure.hpp"
#include "../../../src/range_search/trivial_range_2d.hpp"

TEST(RangeSearch_Interval2DTree, ConstructorTest) {
    interval_2d_tree tree2d(10, 16);
    EXPECT_EQ(tree2d.get_width(), 10) << "Width should be set to 10";
    EXPECT_EQ(tree2d.get_height(), 16) << "Height should be set to 16";
}

TEST(RangeSearch_Interval2DTree, GetSumInRectangleEmptyTest) {
    std::unique_ptr<range_2d> search = std::make_unique<interval_2d_tree>(10, 16);
    EXPECT_EQ(search->get_sum(0, 9, 0, 15), 0) << "Rectangle should be empty";
    EXPECT_EQ(search->get_sum(2, 3, 11, 13), 0) << "Rectangle should be empty";
}

TEST(RangeSearch_Interval2DTree, GetSumInRectangleTest) {
    std::unique_ptr<range_2d> search = std::make_unique<interval_2d_tree>(10, 16);
    search->add_point(1, 2, 1);
    search->add_point(1, 2, 1);
    search->add_point(9, 5, 10);
    EXPECT_EQ(search->get_sum(2, 2, 3, 3), 0) << "Point (2, 3) should be empty";
    EXPECT_EQ(search->get_sum(1, 1, 2, 2), 2) << "Point (1, 2) should have value 2";
    EXPECT_EQ(search->get_sum(9, 9, 5, 5), 10) << "Point (9, 5) should be empty";
    EXPECT_EQ(search->get_sum(1, 9, 1, 8), 12) << "Rectangle [1,9]x[1, 8] should have value 12";
}

void run_random_interval_tree_test(int size, int adds, int sums, std::mt19937& seed) {
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, size - 1);
    std::unique_ptr<range_2d> tst = std::make_unique<interval_2d_tree>(size, size);
    std::unique_ptr<range_2d> ver = std::make_unique<trivial_range2d>(size, size);

    for (int a = 0; a < adds; ++a) {
        int x = dist(seed), y = dist(seed);
        tst->add_point(x, y, 1);
        ver->add_point(x, y, 1);
    }

    for (int s = 0; s < sums; s++) {
        int x0 = dist(seed), x1 = dist(seed);
        if (x0 > x1) std::swap(x0, x1);
        int y0 = dist(seed), y1 = dist(seed);
        if (y0 > y1) std::swap(y0, y1);
        EXPECT_EQ(tst->get_sum(x0, x1, y0, y1), ver->get_sum(x0, x1, y0, y1)) << "RANDOM_TEST";
    }
}

TEST(RangeSearch_Interval2DTree, GetSumInRectangleRandomTest) {
    int tests = 3;
    int maxSize = 30;
    std::random_device rd;
    std::mt19937 seed(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dist_size(1, maxSize);
    for (int t = 0; t < tests; ++t) {
        int size = dist_size(seed);
        run_random_interval_tree_test(size, 5, 5, seed);
    }
}

TEST(RangeSearch_Interval2DTree, GetSumInRectangleRandomLargeTest) {
    int tests = 3;
    int maxSize = 1000;
    int minSize = 500;
    std::random_device rd;
    std::mt19937 seed(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dist_size(minSize, maxSize);
    for (int t = 0; t < tests; ++t) {
        int size = dist_size(seed);
        run_random_interval_tree_test(size, 10000, 1000, seed);
    }
}
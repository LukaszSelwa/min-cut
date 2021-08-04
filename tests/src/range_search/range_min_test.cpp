#include "../../../src/range_search/range_min.hpp"

#include <gtest/gtest.h>

TEST(RangeSearch_RangeMin, SmallTest) {
    std::vector<int> arr{10, 7, 2, 4, 8, 5, 1, 6, 9, 3};
    range_min range;
    range.initialize(&arr[0], &arr[0] + arr.size());

    for (size_t i = 0; i < arr.size(); ++i) {
        EXPECT_EQ(range.min(i, i), arr[i]) << "Min in a single value";
    }

    EXPECT_EQ(range.min(0, 9), 1) << "Min in whole range";
    EXPECT_EQ(range.min(7, 9), 3) << "Min in small range 1";
    EXPECT_EQ(range.min(0, 5), 2) << "Min in small range 2";
    EXPECT_EQ(range.min(1, 4), 2) << "Min in small range 3";
}

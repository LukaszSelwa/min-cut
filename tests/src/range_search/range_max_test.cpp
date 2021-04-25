#include <gtest/gtest.h>
#include "../../../src/range_search/range_max.hpp"

TEST(RangeSearch_RangeMin, SmallTest) {
    std::vector<int> arr{10, 7, 2, 4, 8, 5, 1, 6, 9, 3};
    RangeMax range;
    range.Initialize(&arr[0], &arr[0] + arr.size());

    for (size_t i = 0; i < arr.size(); ++i) {
        EXPECT_EQ(range.Max(i, i), arr[i]) << "Min in a single value";
    }

    EXPECT_EQ(range.Max(0, 9), 10) << "Min in whole range";
    EXPECT_EQ(range.Max(7, 9), 9)  << "Min in small range 1";
    EXPECT_EQ(range.Max(0, 5), 10) << "Min in small range 2";
    EXPECT_EQ(range.Max(1, 4), 8)  << "Min in small range 3";
} 

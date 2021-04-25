#include <gtest/gtest.h>
#include "../../../src/range_search/range_min.hpp"

TEST(RangeSearch_RangeMin, SmallTest) {
    std::vector<int> arr{10, 7, 2, 4, 8, 5, 1, 6, 9, 3};
    RangeMin range;
    range.Initialize(&arr[0], &arr[0] + arr.size());

    for (size_t i = 0; i < arr.size(); ++i) {
        EXPECT_EQ(range.Min(i, i), arr[i]) << "Min in a single value";
    }

    EXPECT_EQ(range.Min(0, 9), 1) << "Min in whole range";
    EXPECT_EQ(range.Min(7, 9), 3) << "Min in small range 1";
    EXPECT_EQ(range.Min(0, 5), 2)<< "Min in small range 2";
    EXPECT_EQ(range.Min(1, 4), 2) << "Min in small range 3";
} 

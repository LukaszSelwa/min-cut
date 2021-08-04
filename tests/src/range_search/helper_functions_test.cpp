#include "../../../src/range_search/helper_functions.hpp"

#include <gtest/gtest.h>

size_t log_ceil(size_t x);

TEST(RangeSearch_HelperFunctions, CeilingLog2) {
    EXPECT_EQ(log_ceil(0), 0) << "test edge case";
    EXPECT_EQ(log_ceil(3), 2) << "test small value";
    EXPECT_EQ(log_ceil(4), 2) << "test power of 2";
    EXPECT_EQ(log_ceil(1 << 16), 16) << "test power of 2";
}
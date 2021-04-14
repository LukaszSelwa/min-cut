#include <gtest/gtest.h>
#include "../../../src/range_search/helper_functions.hpp"

size_t ceilingLog(size_t x);

TEST(RangeSearch_HelperFunctions, CeilingLog2) {
    EXPECT_EQ(ceilingLog(0), 0) << "test edge case";
    EXPECT_EQ(ceilingLog(3), 2) << "test small value";
    EXPECT_EQ(ceilingLog(4), 2) << "test power of 2";
    EXPECT_EQ(ceilingLog(1 << 16), 16) << "test power of 2";
}
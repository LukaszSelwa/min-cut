#include <gtest/gtest.h>

#include "../../../src/utils/functions.hpp"

TEST(Utils_Functions, CeilingLog2) {
    EXPECT_EQ(log_ceil(0), 0) << "test edge case";
    EXPECT_EQ(log_ceil(3), 2) << "test small value";
    EXPECT_EQ(log_ceil(4), 2) << "test power of 2";
    EXPECT_EQ(log_ceil(1 << 16), 16) << "test power of 2";
}
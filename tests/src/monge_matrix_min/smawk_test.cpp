#include <gtest/gtest.h>
#include <functional>
#include "../../../src/monge_matrix_min/smawk.hpp"

TEST(MongeMatrixMin_SMAWK, SmallExampleTest) {
    int mongeArr[7][5] = {
        {10, 17, 13, 28, 23},
        {17, 22, 16, 29, 23},
        {24, 28, 22, 34, 24},
        {11, 13,  6, 17,  7},
        {45, 44, 32, 37, 23},
        {36, 33, 19, 21,  6},
        {75, 66, 51, 53, 34}
    };
    std::vector<size_t> expRowsArgmin{0, 2, 2, 2, 4, 4, 4};
    std::vector<size_t> rowsArgmin(7);
    std::function<int(size_t, size_t)>lookup = [&](size_t row, size_t col) {
        return mongeArr[row][col];
    };
    smawk(7, 5, lookup, rowsArgmin);
    EXPECT_EQ(rowsArgmin, expRowsArgmin);
    EXPECT_EQ(smawk_min(7, 5, lookup), 6);
}
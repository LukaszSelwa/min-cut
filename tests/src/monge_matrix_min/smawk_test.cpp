#include <gtest/gtest.h>
#include <functional>
#include "../../../src/monge_matrix_min/smawk.hpp"

TEST(MongeMatrixMin_SMAWK, SmallExampleTest_1) {
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

TEST(MongeMatrixMin_SMAWK, SmallExampleTest_2) {
    int mongeArr[9][5] = {
        {  25,  21,  13,  10,  20},
        {  42,  35,  26,  20,  29},
        {  57,  48,  35,  28,  33},
        {  78,  65,  51,  42,  44},
        {  90,  76,  58,  48,  49},
        { 103,  85,  67,  56,  55},
        { 123, 105,  86,  75,  73},
        { 142, 123, 100,  86,  82},
        { 151, 130, 104,  88,  80},
    };
    std::vector<size_t> expRowsArgmin{3, 3, 3, 3, 3, 4, 4, 4, 4};
    std::vector<size_t> rowsArgmin(9);
    std::function<int(size_t, size_t)>lookup = [&](size_t row, size_t col) {
        return mongeArr[row][col];
    };
    smawk(9, 5, lookup, rowsArgmin);
    EXPECT_EQ(rowsArgmin, expRowsArgmin);
    EXPECT_EQ(smawk_min(9, 5, lookup), 10);
}

TEST(MongeMatrixMin_SMAWK, mediumExampleTest) {
    int mongeArr[9][18] = {
        {  25,  21,  13,  10,  20,  13,  19,  35,  37,  41,  58,  66,  82,  99, 124, 133, 156, 178},
        {  42,  35,  26,  20,  29,  21,  25,  37,  36,  39,  56,  64,  76,  91, 116, 125, 146, 164},
        {  57,  48,  35,  28,  33,  24,  28,  40,  37,  37,  54,  61,  72,  83, 107, 113, 131, 146},
        {  78,  65,  51,  42,  44,  35,  38,  48,  42,  42,  55,  61,  70,  80, 100, 106, 120, 135},
        {  90,  76,  58,  48,  49,  39,  42,  48,  39,  35,  47,  51,  56,  63,  80,  86,  97, 110},
        { 103,  85,  67,  56,  55,  44,  44,  49,  39,  33,  41,  44,  49,  56,  71,  75,  84,  96},
        { 123, 105,  86,  75,  73,  59,  57,  62,  51,  44,  50,  52,  55,  59,  72,  74,  80,  92},
        { 142, 123, 100,  86,  82,  65,  61,  62,  50,  43,  47,  45,  46,  46,  58,  59,  65,  73},
        { 151, 130, 104,  88,  80,  59,  52,  49,  37,  29,  29,  24,  23,  20,  28,  25,  31,  39},
    };
    std::vector<size_t> expRowsArgmin{3, 3, 5, 5, 9, 9, 9, 9, 13};
    std::vector<size_t> rowsArgmin(9);
    std::function<int(size_t, size_t)>lookup = [&](size_t row, size_t col) {
        return mongeArr[row][col];
    };
    smawk(9, 18, lookup, rowsArgmin);
    EXPECT_EQ(rowsArgmin, expRowsArgmin);
    EXPECT_EQ(smawk_min(9, 18, lookup), 10);
}
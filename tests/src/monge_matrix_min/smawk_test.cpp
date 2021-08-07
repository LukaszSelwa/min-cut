#include "../../../src/monge_matrix_min/smawk.hpp"

#include <gtest/gtest.h>

#include <functional>
#include <random>
#include <sstream>

TEST(MongeMatrixMin_SMAWK, EdgeCase) {
    int mongeArr[1][1] = {
        {10},
    };
    std::vector<size_t> expRowsArgmin{0};
    std::vector<size_t> rowsArgmin(1);
    std::function<int(size_t, size_t)> lookup = [&](size_t row, size_t col) {
        return mongeArr[row][col];
    };
    smawk(1, 1, lookup, rowsArgmin);
    EXPECT_EQ(rowsArgmin, expRowsArgmin);
    min_coords expMin{.row = 0, .col = 0, .val = 10};
    EXPECT_EQ(smawk_min(1, 1, lookup), expMin);
}

TEST(MongeMatrixMin_SMAWK, SmallExampleTest_1) {
    int mongeArr[7][5] = {{10, 17, 13, 28, 23}, {17, 22, 16, 29, 23}, {24, 28, 22, 34, 24},
                          {11, 13, 6, 17, 7},   {45, 44, 32, 37, 23}, {36, 33, 19, 21, 6},
                          {75, 66, 51, 53, 34}};
    std::vector<size_t> expRowsArgmin{0, 2, 2, 2, 4, 4, 4};
    std::vector<size_t> rowsArgmin(7);
    std::function<int(size_t, size_t)> lookup = [&](size_t row, size_t col) {
        return mongeArr[row][col];
    };
    smawk(7, 5, lookup, rowsArgmin);
    EXPECT_EQ(rowsArgmin, expRowsArgmin);
    min_coords expMin{.row = 3, .col = 2, .val = 6};
    EXPECT_EQ(smawk_min(7, 5, lookup), expMin);
}

TEST(MongeMatrixMin_SMAWK, SmallExampleTest_2) {
    int mongeArr[9][5] = {
        {25, 21, 13, 10, 20},   {42, 35, 26, 20, 29},    {57, 48, 35, 28, 33},
        {78, 65, 51, 42, 44},   {90, 76, 58, 48, 49},    {103, 85, 67, 56, 55},
        {123, 105, 86, 75, 73}, {142, 123, 100, 86, 82}, {151, 130, 104, 88, 80},
    };
    std::vector<size_t> expRowsArgmin{3, 3, 3, 3, 3, 4, 4, 4, 4};
    std::vector<size_t> rowsArgmin(9);
    std::function<int(size_t, size_t)> lookup = [&](size_t row, size_t col) {
        return mongeArr[row][col];
    };
    smawk(9, 5, lookup, rowsArgmin);
    EXPECT_EQ(rowsArgmin, expRowsArgmin);
    min_coords expMin{.row = 0, .col = 3, .val = 10};
    EXPECT_EQ(smawk_min(9, 5, lookup), expMin);
}

TEST(MongeMatrixMin_SMAWK, mediumExampleTest) {
    int mongeArr[9][18] = {
        {25, 21, 13, 10, 20, 13, 19, 35, 37, 41, 58, 66, 82, 99, 124, 133, 156, 178},
        {42, 35, 26, 20, 29, 21, 25, 37, 36, 39, 56, 64, 76, 91, 116, 125, 146, 164},
        {57, 48, 35, 28, 33, 24, 28, 40, 37, 37, 54, 61, 72, 83, 107, 113, 131, 146},
        {78, 65, 51, 42, 44, 35, 38, 48, 42, 42, 55, 61, 70, 80, 100, 106, 120, 135},
        {90, 76, 58, 48, 49, 39, 42, 48, 39, 35, 47, 51, 56, 63, 80, 86, 97, 110},
        {103, 85, 67, 56, 55, 44, 44, 49, 39, 33, 41, 44, 49, 56, 71, 75, 84, 96},
        {123, 105, 86, 75, 73, 59, 57, 62, 51, 44, 50, 52, 55, 59, 72, 74, 80, 92},
        {142, 123, 100, 86, 82, 65, 61, 62, 50, 43, 47, 45, 46, 46, 58, 59, 65, 73},
        {151, 130, 104, 88, 80, 59, 52, 49, 37, 29, 29, 24, 23, 20, 28, 25, 31, 39},
    };
    std::vector<size_t> expRowsArgmin{3, 3, 5, 5, 9, 9, 9, 9, 13};
    std::vector<size_t> rowsArgmin(9);
    std::function<int(size_t, size_t)> lookup = [&](size_t row, size_t col) {
        return mongeArr[row][col];
    };
    smawk(9, 18, lookup, rowsArgmin);
    EXPECT_EQ(rowsArgmin, expRowsArgmin);
    min_coords expMin{.row = 0, .col = 3, .val = 10};
    EXPECT_EQ(smawk_min(9, 18, lookup), expMin);
}

void smawk_brutal(size_t numRows, size_t numCols, std::function<int(size_t, size_t)> lookup,
                  std::vector<size_t>& rowsArgmin) {
    for (size_t row = 0; row < numRows; ++row) {
        rowsArgmin[row] = 0;
        int min = lookup(row, 0);
        for (size_t col = 1; col < numCols; ++col) {
            int val = lookup(row, col);
            if (val < min) {
                min = val;
                rowsArgmin[row] = col;
            }
        }
    }
}

min_coords smawk_min_brutal(const size_t numRows, const size_t numCols,
                            std::function<int(size_t, size_t)> lookup) {
    min_coords min{.row = 0, .col = 0, .val = lookup(0, 0)};
    for (size_t row = 0; row < numRows; ++row) {
        for (size_t col = 0; col < numCols; ++col) {
            int val = lookup(row, col);
            if (val < min.val) min = {.row = row, .col = col, .val = val};
        }
    }
    return min;
}

std::vector<std::vector<int> > generate_random_monge_matrix(const size_t numRows,
                                                            const size_t numCols,
                                                            const int initBound, const int maxInc,
                                                            std::mt19937 seed) {
    std::vector<std::vector<int> > mtx(numRows, std::vector<int>(numCols, 0));
    std::uniform_int_distribution<int> distInit(0, initBound);
    std::uniform_int_distribution<int> distInc(0, maxInc);
    std::uniform_int_distribution<int> distDelta(-initBound, initBound);
    for (size_t row = 0; row < numRows; ++row) mtx[row][0] = distInit(seed);

    for (size_t col = 1; col < numCols; ++col) {
        int delta = distDelta(seed);
        for (size_t row = 0; row < numRows; ++row) {
            delta += distInc(seed);
            mtx[row][col] = mtx[row][col - 1] - delta;
        }
    }

    return mtx;
}

std::string get_matrix_info(std::vector<std::vector<int> > mtx) {
    std::stringstream ss;
    ss << "{";
    for (auto& row : mtx) {
        ss << "\n\t{";
        for (auto v : row) ss << ' ' << v << ',';
        ss << "}";
    }
    ss << "\n}";
    return ss.str();
}

void test_random_monge_matrix(const size_t maxSize, const int initBound, const int maxInc,
                              std::mt19937 seed) {
    std::uniform_int_distribution<int> distSize(1, maxSize);
    size_t numRows = distSize(seed);
    size_t numCols = distSize(seed);

    auto mtx = generate_random_monge_matrix(numRows, numCols, initBound, maxInc, seed);
    std::function<int(size_t, size_t)> lookup = [&](size_t row, size_t col) {
        return mtx[row][col];
    };
    ASSERT_EQ(smawk_min(numRows, numCols, lookup), smawk_min_brutal(numRows, numCols, lookup))
        << "Should find minimum for monge matrix: " << get_matrix_info(mtx);

    std::vector<size_t> rowsArgmin(numRows), expRowsArgmin(numRows);
    smawk(numRows, numCols, lookup, rowsArgmin);
    smawk_brutal(numRows, numCols, lookup, expRowsArgmin);
    ASSERT_EQ(rowsArgmin, expRowsArgmin)
        << "Should find rows minimum for monge matrix: " << get_matrix_info(mtx);
}

TEST(MongeMatrixMin_SMAWK, RandomSmallTest) {
    int testCases = 10000;
    int maxSize = 30;
    int initBound = 30;
    int maxInc = 4;

    std::random_device rd;
    std::mt19937 seed;
    while (testCases--) test_random_monge_matrix(maxSize, initBound, maxInc, seed);
}

TEST(MongeMatrixMin_SMAWK, RandomMediumTest) {
    int testCases = 200;
    int maxSize = 500;
    int initBound = 50;
    int maxInc = 3;

    std::random_device rd;
    std::mt19937 seed;
    while (testCases--) test_random_monge_matrix(maxSize, initBound, maxInc, seed);
}

TEST(MongeMatrixMin_SMAWK, RandomLargeTest) {
    int testCases = 20;
    int maxSize = 2000;
    int initBound = 50;
    int maxInc = 2;

    std::random_device rd;
    std::mt19937 seed;
    while (testCases--) test_random_monge_matrix(maxSize, initBound, maxInc, seed);
}
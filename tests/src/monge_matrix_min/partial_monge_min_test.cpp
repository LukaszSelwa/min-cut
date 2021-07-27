#include "../../../src/monge_matrix_min/partial_monge_min.hpp"

#include <gtest/gtest.h>

#include <functional>
#include <random>
#include <sstream>
#include <stdexcept>

TEST(MongeMatrixMin_PartialMonge, EdgeCase) {
    int mongeArr[1][1] = {
        {10},
    };
    std::function<int(size_t, size_t)> lookup = [&](size_t row, size_t col) {
        return mongeArr[row][col];
    };
    min_coords expMin{.row = 0, .col = 0, .val = 10};
    EXPECT_EQ(partial_monge_min(1, lookup), expMin);
}

TEST(MongeMatrixMin_PartialMonge, SmallExampleTest_1) {
    /* clang-format off */
    int mongeArr[5][5] = {
        {10, 17, 13, 28, 23},
        {17, 22, 16, 29, -1},
        {24, 28, 22, -1, -1},
        {11, 13, -1, -1, -1},
        {45, -1, -1, -1, -1}
    };
    /* clang-format on */
    std::function<int(size_t, size_t)> lookup = [&](size_t row, size_t col) {
        if (row + col > 4) {
            std::stringstream ss;
            ss << "should only lookup in lower trinagle but looked-up (" << row << ", " << col
               << ")";
            throw std::invalid_argument(ss.str());
        }
        return mongeArr[row][col];
    };
    min_coords expMin{.row = 0, .col = 0, .val = 10};
    min_coords min = partial_monge_min(5, lookup);
    EXPECT_EQ(min, expMin) << "expected " << expMin << " but got " << min;
}

TEST(MongeMatrixMin_PartialMonge, mediumExampleTest) {
    /* clang-format off */
    int mongeArr[9][9] = {
        { 25,  21,  13,  10,  20,  13,  19,  35,  37},
        { 42,  35,  26,  20,  29,  21,  25,  37,  -1},
        { 57,  48,  35,  28,  33,  24,  28,  -1,  -1},
        { 78,  65,  51,  42,  44,  35,  -1,  -1,  -1},
        { 90,  76,  58,  48,  49,  -1,  -1,  -1,  -1},
        {103,  85,  67,  56,  -1,  -1,  -1,  -1,  -1},
        {123, 105,  86,  -1,  -1,  -1,  -1,  -1,  -1},
        {142, 123,  -1,  -1,  -1,  -1,  -1,  -1,  -1},
        {151,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},
    };
    /* clang-format on */
    std::function<int(size_t, size_t)> lookup = [&](size_t row, size_t col) {
        if (row + col > 8) {
            std::stringstream ss;
            ss << "should only lookup in lower trinagle but looked-up (" << row << ", " << col
               << ")";
            throw std::invalid_argument(ss.str());
        }
        return mongeArr[row][col];
    };
    min_coords expMin{.row = 0, .col = 3, .val = 10};
    EXPECT_EQ(partial_monge_min(9, lookup), expMin);
}

min_coords partial_monge_min_brutal(const size_t size, std::function<int(size_t, size_t)> lookup) {
    min_coords min{.row = 0, .col = 0, .val = lookup(0, 0)};
    for (size_t row = 0; row < size; ++row) {
        for (size_t col = 0; col < size - row; ++col) {
            int val = lookup(row, col);
            if (val < min.val) min = {.row = row, .col = col, .val = val};
        }
    }
    return min;
}

std::vector<std::vector<int> > generate_random_partial_monge_matrix(const size_t size,
                                                                    const int initBound,
                                                                    const int maxInc,
                                                                    std::mt19937 seed) {
    std::vector<std::vector<int> > mtx(size, std::vector<int>(0, 0));
    for (size_t i = 0; i < size; ++i) {
        mtx[i] = std::vector<int>(size - i, 0);
    }

    std::uniform_int_distribution<int> distInit(0, initBound);
    std::uniform_int_distribution<int> distInc(0, maxInc);
    std::uniform_int_distribution<int> distDelta(-initBound, initBound);
    for (size_t row = 0; row < size; ++row) mtx[row][0] = distInit(seed);

    for (size_t col = 1; col < size; ++col) {
        int delta = distDelta(seed);
        for (size_t row = 0; row < size - col; ++row) {
            delta += distInc(seed);
            mtx[row][col] = mtx[row][col - 1] - delta;
        }
    }

    return mtx;
}

std::string get_partial_matrix_info(std::vector<std::vector<int> > mtx) {
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

void test_random_partial_monge_matrix(const size_t maxSize, const int initBound, const int maxInc,
                                      std::mt19937 seed) {
    std::uniform_int_distribution<int> distSize(1, maxSize);
    size_t size = distSize(seed);

    auto mtx = generate_random_partial_monge_matrix(size, initBound, maxInc, seed);

    std::function<int(size_t, size_t)> lookup = [&](size_t row, size_t col) -> int {
        if (row + col >= size) {
            std::stringstream ss;
            ss << "should only lookup in lower trinagle but looked-up (" << row << ", " << col
               << ")";
            throw std::invalid_argument(ss.str());
        }
        return mtx[row][col];
    };
    ASSERT_EQ(partial_monge_min(size, lookup), partial_monge_min_brutal(size, lookup))
        << "Should find minimum for partial monge matrix: " << get_partial_matrix_info(mtx);
}

TEST(MongeMatrixMin_PartialMonge, RandomSmallTest) {
    int testCases = 10000;
    int maxSize = 30;
    int initBound = 30;
    int maxInc = 4;

    std::random_device rd;
    std::mt19937 seed(rd());
    while (testCases--) test_random_partial_monge_matrix(maxSize, initBound, maxInc, seed);
}

TEST(MongeMatrixMin_PartialMonge, RandomMediumTest) {
    int testCases = 200;
    int maxSize = 500;
    int initBound = 50;
    int maxInc = 3;

    std::random_device rd;
    std::mt19937 seed(rd());
    while (testCases--) test_random_partial_monge_matrix(maxSize, initBound, maxInc, seed);
}

TEST(MongeMatrixMin_PartialMonge, RandomLargeTest) {
    int testCases = 20;
    int maxSize = 2000;
    int initBound = 50;
    int maxInc = 2;

    std::random_device rd;
    std::mt19937 seed(rd());
    while (testCases--) test_random_partial_monge_matrix(maxSize, initBound, maxInc, seed);
}
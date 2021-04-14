#include <gtest/gtest.h>
#include <memory>
#include <random>
#include <vector>
#include "../../../src/range_search/interval2D_tree.hpp"
#include "../../../src/range_search/range_search_structure.hpp"

class TrivialRangeSearch: public RangeSearchStructure {
    std::vector<std::vector<int> > arr;
  public:
    TrivialRangeSearch(size_t width, size_t height) {
        arr = std::vector<std::vector<int> > (width, std::vector<int> (height, 0));
    }
    ~TrivialRangeSearch() = default;
    void AddPoint(int x, int y, int val) override {
        arr[x][y] += val;
    }
    int GetSumInRectangle(int x0, int x1, int y0, int y1) override {
        int sum = 0;
        for (int x = x0; x <= x1; ++x) {
            for (int y = y0; y <= y1; ++y)
                sum += arr[x][y];
        }
        return sum;
    }
};

TEST(RangeSearch_Interval2DTree, ConstructorTest) {
    Interval2DTree tree2d(10, 16);
    EXPECT_EQ(tree2d.GetWidth(), 10) << "Width should be set to 10";
    EXPECT_EQ(tree2d.GetHeight(), 16) << "Height should be set to 16";
}

TEST(RangeSearch_Interval2DTree, GetSumInRectangleEmptyTest) {
    std::unique_ptr<RangeSearchStructure> search = std::make_unique<Interval2DTree>(10, 16);
    EXPECT_EQ(search->GetSumInRectangle(0, 9, 0, 15), 0) << "Rectangle should be empty";
    EXPECT_EQ(search->GetSumInRectangle(2, 3, 11, 13), 0) << "Rectangle should be empty";
}

TEST(RangeSearch_Interval2DTree, GetSumInRectangleTest) {
    std::unique_ptr<RangeSearchStructure> search = std::make_unique<Interval2DTree>(10, 16);
    search->AddPoint(1, 2, 1);
    search->AddPoint(1, 2, 1);
    search->AddPoint(9, 5, 10);
    EXPECT_EQ(search->GetSumInRectangle(2, 2, 3, 3), 0)     << "Point (2, 3) should be empty";
    EXPECT_EQ(search->GetSumInRectangle(1, 1, 2, 2), 2)     << "Point (1, 2) should have value 2";
    EXPECT_EQ(search->GetSumInRectangle(9, 9, 5, 5), 10)    << "Point (9, 5) should be empty";
    EXPECT_EQ(search->GetSumInRectangle(1, 9, 1, 8), 12)    << "Rectangle [1,9]x[1, 8] should have value 12";
}

void RunSingleRandomTest(int size, int adds, int sums, std::mt19937 & seed) {
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, size - 1);
    std::unique_ptr<RangeSearchStructure> tst = std::make_unique<Interval2DTree> (size, size);
    std::unique_ptr<RangeSearchStructure> ver = std::make_unique<TrivialRangeSearch> (size, size);

    for (int a = 0; a < adds; ++a) {
        int x = dist(seed), y = dist(seed);
        tst->AddPoint(x, y, 1);
        ver->AddPoint(x, y, 1);
    }

    for (int s = 0; s < sums; s++) {
        int x0 = dist(seed), x1 = dist(seed);
        if (x0 > x1) std::swap(x0, x1);
        int y0 = dist(seed), y1 = dist(seed);
        if (y0 > y1) std::swap(y0, y1);
        EXPECT_EQ(tst->GetSumInRectangle(x0, x1, y0, y1), ver->GetSumInRectangle(x0, x1, y0, y1)) << "RANDOM_TEST";
    }
}

TEST(RangeSearch_Interval2DTree, GetSumInRectangleRandomTest) {
    int tests = 3;
    int maxSize = 30;
    std::random_device rd;
    std::mt19937 seed(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dist_size(1, maxSize);
    for (int t = 0; t < tests; ++t) {
        int size = dist_size(seed);
        RunSingleRandomTest(size, 5, 5, seed);
    }
}

TEST(RangeSearch_Interval2DTree, GetSumInRectangleRandomLargeTest) {
    int tests = 3;
    int maxSize = 1000;
    int minSize = 500;
    std::random_device rd;
    std::mt19937 seed(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dist_size(minSize, maxSize);
    for (int t = 0; t < tests; ++t) {
        int size = dist_size(seed);
        RunSingleRandomTest(size, 10000, 1000, seed);
    }
}
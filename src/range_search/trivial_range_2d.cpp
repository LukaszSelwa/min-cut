#include "trivial_range_2d.hpp"

trivial_range2d::trivial_range2d(size_t width, size_t height) {
    arr = std::vector<std::vector<int> >(width, std::vector<int>(height, 0));
}

void trivial_range2d::add_point(int x, int y, int val) { arr[x][y] += val; }

int trivial_range2d::get_sum(int x0, int x1, int y0, int y1) {
    int sum = 0;
    for (int x = x0; x <= x1; ++x) {
        for (int y = y0; y <= y1; ++y) sum += arr[x][y];
    }
    return sum;
}
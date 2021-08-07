#include "interval2D_tree.hpp"

#include "helper_functions.hpp"
#include "../utils/functions.hpp"

interval_2d_tree::interval_2d_tree(size_t width, size_t height) : width(width), height(height) {
    size_t hLog = log_ceil(height);
    nrLeaves = 1 << hLog;
    trees = std::vector<interval_tree>(2 * nrLeaves + 1, interval_tree(width));
}

void interval_2d_tree::add_point(int x, int y, int val) {
    int tY = get_tree_index(y);
    trees[tY].add_point(x, val);
    while (tY > 1) {
        tY = parent_interval(tY);
        update_base_tree(tY, x);
    }
}

int interval_2d_tree::get_sum(int x0, int x1, int y0, int y1) {
    if (x0 > x1 || y0 > y1) return 0;
    int sum = 0;
    int tY0 = get_tree_index(y0), tY1 = get_tree_index(y1);
    while (tY0 <= tY1) {
        if (is_right_child(tY0)) {
            sum += trees[tY0].sum(x0, x1);
            tY0++;
        }
        if (is_left_child(tY1)) {
            sum += trees[tY1].sum(x0, x1);
            tY1--;
        }
        tY0 = parent_interval(tY0);
        tY1 = parent_interval(tY1);
    }
    return sum;
}

size_t interval_2d_tree::get_width() { return width; }
size_t interval_2d_tree::get_height() { return height; }

int interval_2d_tree::get_tree_index(int idx) { return idx + nrLeaves; }

void interval_2d_tree::update_base_tree(int tY, int x) {
    trees[tY].set_point(x, trees[left_child_interval(tY)].get_point(x) +
                               trees[right_child_interval(tY)].get_point(x));
}
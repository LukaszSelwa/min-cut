#include "segment_2d_point_tree.hpp"

segment_2d_point_tree::segment_2d_point_tree(size_t size)
    : root(std::make_unique<interval_point<2, int>>(size)) {}

void segment_2d_point_tree::add_point(int x, int y, int val) { root->add_point(val, x, y); }

int segment_2d_point_tree::get_sum(int x0, int x1, int y0, int y1) {
    return root->get_sum(x0, x1, y0, y1);
}
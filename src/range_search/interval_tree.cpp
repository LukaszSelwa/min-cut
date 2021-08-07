#include "interval_tree.hpp"

#include "../utils/functions.hpp"
#include "helper_functions.hpp"

interval_tree::interval_tree(size_t size) : size(size) {
    size_t log = log_ceil(size);
    nrLeaves = 1 << log;
    baseIntervals = std::vector<int>(2 * nrLeaves + 1, 0);
}

void interval_tree::add_point(int idx, int val) { set_point(idx, val + get_point(idx)); }

void interval_tree::set_point(int idx, int val) {
    int tIdx = get_tree_index(idx);
    baseIntervals[tIdx] = val;
    while (tIdx > 1) {
        tIdx = parent_interval(tIdx);
        update_base_interval(tIdx);
    }
}

int interval_tree::sum(int begin, int end) {
    int sum = 0;
    int tBegin = get_tree_index(begin), tEnd = get_tree_index(end);
    while (tBegin <= tEnd) {
        if (is_right_child(tBegin)) {
            sum += baseIntervals[tBegin];
            tBegin++;
        }
        if (is_left_child(tEnd)) {
            sum += baseIntervals[tEnd];
            tEnd--;
        }
        tBegin = parent_interval(tBegin);
        tEnd = parent_interval(tEnd);
    }
    return sum;
}

int interval_tree::get_point(int idx) { return baseIntervals[get_tree_index(idx)]; }

void interval_tree::update_base_interval(int tIdx) {
    baseIntervals[tIdx] =
        baseIntervals[left_child_interval(tIdx)] + baseIntervals[right_child_interval(tIdx)];
}

int interval_tree::get_tree_index(int idx) { return idx + nrLeaves; }

size_t interval_tree::get_size() const { return size; }
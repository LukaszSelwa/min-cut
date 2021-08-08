#include "suffix_tree.hpp"

#include "../utils/functions.hpp"

void suffix_tree::recalc_segment(int segIdx) {
    segments[segIdx].rightLeaf =
        segments[2 * segIdx + 1].rightLeaf + segments[2 * segIdx + 1].modSum;
}

suffix_tree::suffix_tree(size_t size) {
    size_t log = log_ceil(size);
    nrLeaves = 1 << log;
    segments = std::vector<suffix_tree_segment>(2 * nrLeaves + 1, suffix_tree_segment{0, 0});
}

void suffix_tree::add_to_suffix(int suf, int val, int segIdx, int begin, int end) {
    if (suf == begin) {
        segments[segIdx].modSum += val;
        return;
    }
    int mid = (begin + end) / 2;
    if (suf < mid) {
        add_to_suffix(suf, val, 2 * segIdx, begin, mid);
        segments[2 * segIdx + 1].modSum += val;
    } else {
        add_to_suffix(suf, val, 2 * segIdx + 1, mid, end);
    }
    recalc_segment(segIdx);
}

void suffix_tree::add_to_suffix(int suf, int val) { add_to_suffix(suf, val, 1, 0, nrLeaves); }

int suffix_tree::first_geq_idx(int val) {
    int segIdx = 1;
    while (segIdx < nrLeaves) {
        val -= segments[segIdx].modSum;
        int mid = segments[2 * segIdx].rightLeaf;
        if (val <= mid)
            segIdx = 2 * segIdx;
        else
            segIdx = 2 * segIdx + 1;
    }
    return segIdx - nrLeaves;
}
#include "interval_tree.hpp"
#include "helper_functions.hpp"

IntervalTree::IntervalTree(size_t size): size(size) {
    size_t log = ceilingLog(size);
    nrLeaves = 1 << log;
    baseIntervals = std::vector<int>(2 * nrLeaves + 1, 0);
}

void IntervalTree::AddPoint(int idx, int val) {
    int tIdx = getTreeIndex(idx);
    baseIntervals[tIdx] += val;
    while (tIdx > 1) {
        tIdx = parentInterval(tIdx);
        updateBaseInterval(tIdx);
    }
}

int IntervalTree::SumInRange(int begin, int end) {
    int sum = 0;
    int tBegin = getTreeIndex(begin), tEnd = getTreeIndex(end);
    while (tBegin <= tEnd) {
        if (isRightChild(tBegin)) {
            sum += baseIntervals[tBegin];
            tBegin++;
        }
        if (isLeftChild(tEnd)) {
            sum += baseIntervals[tEnd];
            tEnd--;
        }
        tBegin = parentInterval(tBegin);
        tEnd = parentInterval(tEnd);
    }
    
    return sum;
}

void IntervalTree::updateBaseInterval (int tIdx) {
    baseIntervals[tIdx] = baseIntervals[leftChildInterval(tIdx)] + baseIntervals[rightChildInterval(tIdx)];
}

int IntervalTree::getTreeIndex (int idx) {
    return idx + nrLeaves;
}

size_t IntervalTree::GetSize () const {
    return size;
}
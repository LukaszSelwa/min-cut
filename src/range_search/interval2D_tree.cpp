#include "interval2D_tree.hpp"
#include "helper_functions.hpp"

Interval2DTree::Interval2DTree(size_t width, size_t height): width(width), height(height) {
    size_t hLog = ceilingLog(height);
    nrLeaves = 1 << hLog;
    trees = std::vector<IntervalTree>(2 * nrLeaves + 1, IntervalTree(width));
}

void Interval2DTree::AddPoint(int x, int y, int val) {
    int tY = getTreeIndex(y);
    trees[tY].AddPoint(x, val);
    while (tY > 1) {
        tY = parentInterval(tY);
        updateBaseTree(tY, x);
    }
}

int Interval2DTree::GetSumInRectangle(int x0, int x1, int y0, int y1) {
    int sum = 0;
    int tY0 = getTreeIndex(y0), tY1 = getTreeIndex(y1);
    while (tY0 <= tY1) {
        if (isRightChild(tY0)) {
            sum += trees[tY0].SumInRange(x0, x1);
            tY0++;
        }
        if (isLeftChild(tY1)) {
            sum += trees[tY1].SumInRange(x0, x1);
            tY1--;
        }
        tY0 = parentInterval(tY0);
        tY1 = parentInterval(tY1);
    }
    return sum;
}

size_t Interval2DTree::GetWidth() { return width; }
size_t Interval2DTree::GetHeight() { return height; }

int Interval2DTree::getTreeIndex (int idx) {
    return idx + nrLeaves;
}

void Interval2DTree::updateBaseTree (int tY, int x) {
    trees[tY].SetPoint(
        x,
        trees[leftChildInterval(tY)].PointVal(x) + trees[rightChildInterval(tY)].PointVal(x)
    );
}
#ifndef INTERVAL2D_TREE
#define INTERVAL2D_TREE
#include <vector>

#include "interval_tree.hpp"
#include "range_search_structure.hpp"

class Interval2DTree : public RangeSearchStructure {
    size_t width, height;
    int nrLeaves;
    std::vector<IntervalTree> trees;

   public:
    Interval2DTree(size_t width, size_t height);
    ~Interval2DTree() = default;
    void AddPoint(int x, int y, int val) override;
    int GetSumInRectangle(int x0, int x1, int y0, int y1) override;
    size_t GetWidth();
    size_t GetHeight();

   private:
    void updateBaseTree(int tY, int x);
    inline int getTreeIndex(int idx);
};

#endif /* INTERVAL2D_TREE */
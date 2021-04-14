#ifndef INTERVAL2D_TREE
#define INTERVAL2D_TREE
#include "range_search_structure.hpp"

class Interval2DTree: public RangeSearchStructure {
  public:
    Interval2DTree(int width, int height);
    void AddPoint(int x, int y, int val);
    int GetSumInRectangle(int x0, int y0, int x1, int y1);
};

#endif /* INTERVAL2D_TREE */
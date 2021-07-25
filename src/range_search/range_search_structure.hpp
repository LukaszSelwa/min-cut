#ifndef RANGE_SEARCH_STRUCTURE
#define RANGE_SEARCH_STRUCTURE

class RangeSearchStructure {
   public:
    virtual void AddPoint(int x, int y, int val) = 0;
    virtual int GetSumInRectangle(int x0, int x1, int y0, int y1) = 0;
    virtual ~RangeSearchStructure() = default;
};

#endif /* RANGE_SEARCH_STRUCTURE */
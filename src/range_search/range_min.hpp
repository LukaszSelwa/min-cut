#ifndef RANGE_MIN
#define RANGE_MIN

#include <vector>

class RangeMin {
    std::vector<std::vector<int> > pow2mins;
    std::vector<int> florLog2lookup;
  public:
    RangeMin(int* begin, int* end);
    void Initialize();
    /* returns minimum value in range [beginIdx, endIdx]*/
    int Min(int beginIdx, int endIdx);
};

#endif /* RANGE_MIN */
#ifndef RANGE_MIN
#define RANGE_MIN

#include <vector>

class RangeMax {
    std::vector<std::vector<int> > pow2mins;
    std::vector<int> florLog2lookup;
  public:
    RangeMax() { }
    void Initialize(int* begin, int* end);
    /* returns minimum value in range [beginIdx, endIdx]*/
    int Max(int beginIdx, int endIdx);

  private:
    void SetUpLookup(size_t size);
};

#endif /* RANGE_MIN */
#ifndef RANGE_MIN
#define RANGE_MIN

#include <vector>

class range_min {
    std::vector<std::vector<int> > pow2mins;
    std::vector<int> florLog2lookup;

   public:
    range_min() {}
    void initialize(int* begin, int* end);
    /* returns minimum value in range [beginIdx, endIdx]*/
    int min(int beginIdx, int endIdx);

   private:
    void set_up_lookup(size_t size);
};

#endif /* RANGE_MIN */
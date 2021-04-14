#ifndef INTERVAL_TREE
#define INTERVAL_TREE
#include <vector>

class IntervalTree {
    size_t size;
    int nrLeaves;
    std::vector<int> baseIntervals;

  public:
    IntervalTree(size_t size);
    IntervalTree(): IntervalTree(0) { }
    void AddPoint(int idx, int val);
    
    /* Inclusive range: [begin, end] */
    int SumInRange(int begin, int end);
    size_t GetSize() const;
  private:
    void updateBaseInterval(int tIdx);
    inline int getTreeIndex(int idx);
};

#endif /* INTERVAL_TREE */
#ifndef UTILS__PREFIX_TREE_H
#define UTILS__PREFIX_TREE_H
#include <algorithm>
#include <vector>

struct suffix_tree_segment {
    int modSum;
    int rightLeaf;
};

class suffix_tree {
    int nrLeaves;
    std::vector<suffix_tree_segment> segments;
    void recalc_segment(int segIdx);
    void add_to_suffix(int suf, int val, int segIdx, int begin, int end);

   public:
    suffix_tree(size_t size);
    void add_to_suffix(int suf, int val);
    int first_geq_idx(int val);
};

#endif /* UTILS__PREFIX_TREE_H */
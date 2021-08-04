#ifndef SEGMENT_2D_POINT_TREE
#define SEGMENT_2D_POINT_TREE
#include <memory>

#include "interval_point.hpp"
#include "range_search_structure.hpp"

class segment_2d_point_tree : public range_2d {
    std::unique_ptr<interval_point<2, int>> root;

   public:
    segment_2d_point_tree(size_t size);
    ~segment_2d_point_tree() = default;
    void add_point(int x, int y, int val) override;
    int get_sum(int x0, int x1, int y0, int y1) override;
};

#endif /* SEGMENT_2D_POINT_TREE */
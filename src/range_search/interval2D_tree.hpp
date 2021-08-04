#ifndef INTERVAL2D_TREE
#define INTERVAL2D_TREE
#include <vector>

#include "interval_tree.hpp"
#include "range_search_structure.hpp"

class interval_2d_tree : public range_2d {
    size_t width, height;
    int nrLeaves;
    std::vector<interval_tree> trees;

   public:
    interval_2d_tree(size_t width, size_t height);
    ~interval_2d_tree() = default;
    void add_point(int x, int y, int val) override;
    int get_sum(int x0, int x1, int y0, int y1) override;
    size_t get_width();
    size_t get_height();

   private:
    void update_base_tree(int tY, int x);
    inline int get_tree_index(int idx);
};

#endif /* INTERVAL2D_TREE */
#include <vector>

#include "range_search_structure.hpp"

class trivial_range2d : public range_2d {
    std::vector<std::vector<int> > arr;

   public:
    trivial_range2d(size_t width, size_t height);
    ~trivial_range2d() = default;
    void add_point(int x, int y, int val) override;
    int get_sum(int x0, int x1, int y0, int y1) override;
};
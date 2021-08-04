#ifndef RANGE_SEARCH_STRUCTURE
#define RANGE_SEARCH_STRUCTURE

class range_2d {
   public:
    virtual void add_point(int x, int y, int val) = 0;
    virtual int get_sum(int x0, int x1, int y0, int y1) = 0;
    virtual ~range_2d() = default;
};

#endif /* RANGE_SEARCH_STRUCTURE */
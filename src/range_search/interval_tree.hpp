#ifndef INTERVAL_TREE
#define INTERVAL_TREE
#include <vector>

class interval_tree {
    size_t size;
    int nrLeaves;
    std::vector<int> baseIntervals;

   public:
    interval_tree(size_t size);
    interval_tree() : interval_tree(0) {}
    void add_point(int idx, int val);
    void set_point(int idx, int val);

    /* Inclusive range: [begin, end] */
    int sum(int begin, int end);
    int get_point(int idx);
    size_t get_size() const;

   private:
    void update_base_interval(int tIdx);
    inline int get_tree_index(int idx);
};

#endif /* INTERVAL_TREE */
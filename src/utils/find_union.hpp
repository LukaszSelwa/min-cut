#ifndef UTILS__FIND_UNION_H
#define UTILS__FIND_UNION_H

#include <vector>

struct fu_element {
    int parent;
    int size;
};

class find_union {
   private:
    std::vector<fu_element> elements;
    int maxCluster;
    int get_top_parent(int id);

   public:
    find_union(size_t size);
    void unite(int aId, int bId);
    bool are_united(int aId, int bId);
    int get_max_cluster_size();
};

#endif /* UTILS__FIND_UNION_H */
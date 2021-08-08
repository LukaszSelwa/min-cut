#include "find_union.hpp"

#include <algorithm>

find_union::find_union(size_t size)
    : elements(size, fu_element{.parent = -1, .size = 1}), maxCluster(1) {}

int find_union::get_top_parent(int id) {
    if (elements[id].parent == -1) return id;
    int topParent = get_top_parent(elements[id].parent);
    elements[id].parent = topParent;
    return topParent;
}

void find_union::unite(int aId, int bId) {
    int aParent = get_top_parent(aId);
    int bParent = get_top_parent(bId);

    if (aParent != bParent) {
        elements[aParent].size += elements[bParent].size;
        elements[bParent].parent = aParent;
        maxCluster = std::max(maxCluster, elements[aParent].size);
    }
}

bool find_union::are_united(int aId, int bId) {
    int aParent = get_top_parent(aId);
    int bParent = get_top_parent(bId);

    return aParent == bParent;
}

int find_union::get_max_cluster_size() { return maxCluster; }
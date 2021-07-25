#ifndef TREE
#define TREE
#include <functional>
#include <iostream>
#include <vector>

#include "vertices.hpp"

namespace graphs {

class tree_vertice {
   public:
    int idx;
    int bottomCrossinterested;
    int bottomDowninterested;
    int hlPathId;
    w_edge parentEdge;
    std::vector<w_edge> children;

    tree_vertice() : idx(0), parentEdge(0, -1, 0), children(0) {}
};

class weighted_tree {
   public:
    size_t size;
    int rootIdx;
    std::vector<tree_vertice> vertices;

    weighted_tree(size_t size);
    weighted_tree() : weighted_tree(0) {}
    void add_child_edge(int parent, int child, int weight);
    void run_preorder(std::function<void(tree_vertice&)> func);
    void run_postorder(std::function<void(tree_vertice&)> func);
    friend std::ostream& operator<<(std::ostream& o, const weighted_tree& tree);

   private:
    void run_preorder(int idx, std::function<void(tree_vertice&)>& func);
    void run_postorder(int idx, std::function<void(tree_vertice&)>& func);
};

}  // namespace graphs

#endif /* TREE */
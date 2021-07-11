#include "weighted_tree.hpp"

namespace graphs {

weighted_tree::weighted_tree(size_t size): size(size), rootIdx(0), vertices(std::vector<tree_vertice>(size)) {
    for (int i = 0; i < size; ++i)
        vertices[i].idx = i;
}

void weighted_tree::add_child_edge(int parent, int child, int weight) {
    vertices[parent].children.emplace_back(parent, child, weight);
    vertices[child].parentEdge = w_edge(child, parent, weight);
}

void weighted_tree::run_preorder(std::function<void(tree_vertice&)> func) {
    run_preorder(rootIdx, func);
}

void weighted_tree::run_preorder(int idx, std::function<void(tree_vertice&)> & func) {
    func(vertices[idx]);
    for (auto & edge : vertices[idx].children)
        run_preorder(edge.destIdx, func);
}

void weighted_tree::run_postorder(std::function<void(tree_vertice&)> func) {
    run_postorder(rootIdx, func);
}

void weighted_tree::run_postorder(int idx, std::function<void(tree_vertice&)> & func) {
    for (auto & edge : vertices[idx].children)
        run_postorder(edge.destIdx, func);
    func(vertices[idx]);
}

std::ostream & operator<< (std::ostream & o, const weighted_tree & tree) {
    o << "tree[size: "<< tree.size << "]{\n";
    for (auto & v : tree.vertices) {
        o << "\t" << v.idx << ": ";
        for (auto & e : v.children)
            o << e << ", ";
        o << "\n";
    }
    o << "}";
    return o;
}

}
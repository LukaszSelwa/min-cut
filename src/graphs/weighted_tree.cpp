#include "weighted_tree.hpp"

namespace graphs {

WeightedTree::WeightedTree(size_t size): size(size), rootIdx(0), vertices(std::vector<TreeVertice>(size)) {
    for (int i = 0; i < size; ++i)
        vertices[i].idx = i;
}

void WeightedTree::AddChildEdge(int parent, int child, int weight) {
    vertices[parent].children.emplace_back(parent, child, weight);
    vertices[child].parentEdge = w_edge(child, parent, weight);
}

void WeightedTree::RunPreOrder(std::function<void(TreeVertice&)> func) {
    RunPreOrder(rootIdx, func);
}

void WeightedTree::RunPreOrder(int idx, std::function<void(TreeVertice&)> & func) {
    func(vertices[idx]);
    for (auto & edge : vertices[idx].children)
        RunPreOrder(edge.destIdx, func);
}

void WeightedTree::RunPostOrder(std::function<void(TreeVertice&)> func) {
    RunPostOrder(rootIdx, func);
}

void WeightedTree::RunPostOrder(int idx, std::function<void(TreeVertice&)> & func) {
    for (auto & edge : vertices[idx].children)
        RunPostOrder(edge.destIdx, func);
    func(vertices[idx]);
}

std::ostream & operator<< (std::ostream & o, const WeightedTree & tree) {
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
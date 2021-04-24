#include "weighted_tree.hpp"

namespace graphs {

WeightedTree::WeightedTree(size_t size): rootIdx(0), vertices(std::vector<Vertice>(size)) {
    for (int i = 0; i < size; ++i)
        vertices[i].SetMyIdx(i);
}

void WeightedTree::AddEdge(int idx1, int idx2, int weight) {
    vertices[idx1].AddNeighbour(idx2, weight);
    vertices[idx2].AddNeighbour(idx1, weight);
}

void WeightedTree::RunPreOrder(std::function<void(Vertice&)> func) {
    RunPreOrder(rootIdx, -1, func);
}

void WeightedTree::RunPreOrder(int idx, int parentIdx, std::function<void(Vertice&)> func) {
    func(vertices[idx]);
    for (auto & edge : vertices[idx].GetNeighbors()) {
        if (edge.destIdx != parentIdx) 
            RunPreOrder(edge.destIdx, idx, func);
    }
}

}
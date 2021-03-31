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

}
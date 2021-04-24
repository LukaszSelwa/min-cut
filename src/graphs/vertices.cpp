#include "vertices.hpp"

namespace graphs {

void Vertice::AddNeighbour(int idx, int weight) {
    Neighbors.push_back(WeightedEdge(myIdx, idx, weight));
}

int Vertice::GetIdx() {
    return myIdx;
}

void Vertice::SetMyIdx(int idx) {
    myIdx = idx;
}

const std::vector<WeightedEdge> & Vertice::GetNeighbors() {
    return Neighbors;
}

}
#include "vertices.hpp"

namespace graphs {

bool WeightedEdge::IsEqual(const WeightedEdge & e) {
    return (srcIdx == e.srcIdx && destIdx == e.destIdx)
        || (destIdx == e.srcIdx && srcIdx == e.destIdx);
}

std::ostream & operator<< (std::ostream &os, const WeightedEdge & e) {
    return os << "(" << e.srcIdx << "->" << e.destIdx << ", " << e.weight << ")";
}

void Vertice::AddNeighbour(int idx, int weight) {
    Neighbors.push_back(WeightedEdge(myIdx, idx, weight));
}

int Vertice::GetIdx() const {
    return myIdx;
}

void Vertice::SetMyIdx(int idx) {
    myIdx = idx;
}

std::vector<WeightedEdge> & Vertice::GetNeighbors() {
    return Neighbors;
}

const std::vector<WeightedEdge> & Vertice::GetNeighbors() const {
    return Neighbors;
}

}
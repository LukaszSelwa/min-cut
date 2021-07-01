#include "vertices.hpp"

namespace graphs {

bool w_edge::is_equal(const w_edge & e) {
    return (srcIdx == e.srcIdx && destIdx == e.destIdx)
        || (destIdx == e.srcIdx && srcIdx == e.destIdx);
}

std::ostream & operator<< (std::ostream &os, const w_edge & e) {
    return os << "(" << e.srcIdx << "->" << e.destIdx << ", " << e.weight << ")";
}

void vertice::add_neighbour(int idx, int weight) {
    neighbors.push_back(w_edge(myIdx, idx, weight));
}

int vertice::get_idx() const {
    return myIdx;
}

void vertice::set_idx(int idx) {
    myIdx = idx;
}

}
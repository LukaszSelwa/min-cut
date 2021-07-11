#include "vertices.hpp"

namespace graphs {

bool w_edge::is_equal(const w_edge & e) const {
    return (srcIdx == e.srcIdx && destIdx == e.destIdx)
        || (destIdx == e.srcIdx && srcIdx == e.destIdx);
}

std::ostream & operator<< (std::ostream &os, const w_edge & e) {
    return os << "(" << e.srcIdx << "->" << e.destIdx << ", " << e.weight << ")";
}

bool operator== (const w_edge & e1, const w_edge & e2) {
    return e1.is_equal(e2);
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
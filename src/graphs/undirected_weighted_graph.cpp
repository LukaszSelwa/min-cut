#include "undirected_weighted_graph.hpp"

namespace graphs {

weighted_graph::weighted_graph (size_t size): size(size), vertices(std::vector<vertice>(size)) {
    for (int i = 0; i < size; ++i)
        vertices[i].set_idx(i);
}

void weighted_graph::add_edge(const w_edge edge) {
    vertices[edge.srcIdx].add_neighbour(edge.destIdx, edge.weight);
    vertices[edge.destIdx].add_neighbour(edge.srcIdx, edge.weight);
}

vertice & weighted_graph::operator[] (size_t idx) {
    return vertices[idx];
}

std::ostream & operator<< (std::ostream & o, const weighted_graph & graph) {
    o << "graph[size: " << graph.size << "]{\n";
    for (auto & v : graph.vertices) {
        o << "\t" << v.get_idx() << ": ";
        for (auto & e : v.neighbors)
            o << e << ", ";
        o << "\n";
    }
    o << "}";
    return o;
}

}
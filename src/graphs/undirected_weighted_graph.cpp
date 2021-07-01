#include "undirected_weighted_graph.hpp"

namespace graphs {

weighted_graph::weighted_graph (size_t size): size(size), vertices(std::vector<Vertice>(size)) {
    for (int i = 0; i < size; ++i)
        vertices[i].SetMyIdx(i);
}

void weighted_graph::add_edge(const WeightedEdge edge) {
    vertices[edge.srcIdx].AddNeighbour(edge.destIdx, edge.weight);
    vertices[edge.destIdx].AddNeighbour(edge.srcIdx, edge.weight);
}

Vertice & weighted_graph::operator[] (size_t idx) {
    return vertices[idx];
}

std::ostream & operator<< (std::ostream & o, const weighted_graph & graph) {
    o << "graph[size: " << graph.size << "]{\n";
    for (auto & v : graph.vertices) {
        o << "\t" << v.GetIdx() << ": ";
        for (auto & e : v.neighbors)
            o << e << ", ";
        o << "\n";
    }
    o << "}";
    return o;
}

}
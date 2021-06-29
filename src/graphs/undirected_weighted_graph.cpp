#include "undirected_weighted_graph.hpp"

namespace graphs {

UndirectedWeightedGraph::UndirectedWeightedGraph (size_t size): size(size), vertices(std::vector<Vertice>(size)) {
    for (int i = 0; i < size; ++i)
        vertices[i].SetMyIdx(i);
}

int UndirectedWeightedGraph::GetSize() const {
    return vertices.size();
}

void UndirectedWeightedGraph::AddEdge(const WeightedEdge edge) {
    vertices[edge.srcIdx].AddNeighbour(edge.destIdx, edge.weight);
    vertices[edge.destIdx].AddNeighbour(edge.srcIdx, edge.weight);
}

Vertice & UndirectedWeightedGraph::operator[] (size_t idx) {
    return vertices[idx];
}

std::ostream & operator<< (std::ostream & o, const UndirectedWeightedGraph & graph) {
    o << "graph[size: " << graph.size << "]{\n";
    for (auto & v : graph.vertices) {
        o << v.GetIdx() << ": ";
        for (auto & e : v.neighbors)
            o << e << ", ";
        o << "\n";
    }
    o << "}";
    return o;
}

}
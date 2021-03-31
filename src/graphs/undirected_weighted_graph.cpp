#include "undirected_weighted_graph.hpp"

namespace graphs {

UndirectedWeightedGraph::UndirectedWeightedGraph(size_t size): vertices(std::vector<Vertice>(size)) {
    for (int i = 0; i < size; ++i)
        vertices[i].SetMyIdx(i);
}

int UndirectedWeightedGraph::GetSize() const {
    return vertices.size();
}

}
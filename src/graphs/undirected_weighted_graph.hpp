#ifndef UNDIRECTED_WEIGHTED_GRAPH
#define UNDIRECTED_WEIGHTED_GRAPH
#include <vector>
#include "vertices.hpp"

namespace graphs {

class UndirectedWeightedGraph {
    std::vector<Vertice> vertices;

  public:
    UndirectedWeightedGraph(size_t size);
    int GetSize() const;
    void AddEdge();
    Vertice & operator[] (size_t i);
};

}
#endif /* !UNDIRECTED_WEIGHTED_GRAPH */
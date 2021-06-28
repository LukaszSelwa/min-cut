#ifndef UNDIRECTED_WEIGHTED_GRAPH
#define UNDIRECTED_WEIGHTED_GRAPH
#include <iostream>
#include <vector>
#include "vertices.hpp"

namespace graphs {

class UndirectedWeightedGraph {
  public:
    const size_t size;
    std::vector<Vertice> vertices;
    UndirectedWeightedGraph(size_t size);
    int GetSize() const;
    void AddEdge(const WeightedEdge edge);
    Vertice & operator[] (size_t i);
    friend std::ostream & operator<< (std::ostream & o, const UndirectedWeightedGraph & graph);
};

}
#endif /* !UNDIRECTED_WEIGHTED_GRAPH */
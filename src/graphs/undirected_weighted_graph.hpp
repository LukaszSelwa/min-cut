#ifndef UNDIRECTED_WEIGHTED_GRAPH
#define UNDIRECTED_WEIGHTED_GRAPH
#include <vector>
#include "vertices.hpp"

namespace graphs {

class UndirectedWeightedGraph {
    std::vector<Vertice> vertices;

  public:
    UndirectedWeightedGraph(size_t size);
};

}
#endif /* !UNDIRECTED_WEIGHTED_GRAPH */
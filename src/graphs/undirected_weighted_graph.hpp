#ifndef UNDIRECTED_WEIGHTED_GRAPH
#define UNDIRECTED_WEIGHTED_GRAPH
#include <iostream>
#include <vector>

#include "vertices.hpp"

namespace graphs {

class weighted_graph {
   public:
    const size_t size;
    std::vector<vertice> vertices;
    weighted_graph(size_t size);
    void add_edge(const w_edge edge);
    vertice& operator[](size_t i);
    friend std::ostream& operator<<(std::ostream& o, const weighted_graph& graph);
};

}  // namespace graphs
#endif /* !UNDIRECTED_WEIGHTED_GRAPH */
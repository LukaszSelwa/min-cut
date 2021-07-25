#ifndef GRAPH_EXAMPLES_H
#define GRAPH_EXAMPLES_H
#include <memory>

#include "../graphs/undirected_weighted_graph.hpp"
#include "../graphs/weighted_tree.hpp"

namespace examples {
using namespace graphs;

struct graph_example {
    std::shared_ptr<weighted_graph> graph;
    std::shared_ptr<weighted_tree> spanningTree;
};

graph_example get_example(int nr);

}  // namespace examples
#endif /* GRAPH_EXAMPLES_H */
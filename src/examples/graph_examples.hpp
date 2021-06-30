#ifndef GRAPH_EXAMPLES_H
#define GRAPH_EXAMPLES_H
#include "../graphs/weighted_tree.hpp"
#include "../graphs/undirected_weighted_graph.hpp"
#include <memory>

namespace examples {
using namespace graphs;

struct graph_example {
    std::shared_ptr<UndirectedWeightedGraph> graph;
    std::shared_ptr<WeightedTree> spanningTree; 
};

graph_example get_example(int nr);

}
#endif /* GRAPH_EXAMPLES_H */
#ifndef INPUT_GRAPH_H
#define INPUT_GRAPH_H

#include <iostream>
#include <memory>

#include "../graphs/undirected_weighted_graph.hpp"
#include "../graphs/weighted_tree.hpp"

namespace examples {
using namespace graphs;

struct input_graph {
    std::shared_ptr<weighted_graph> graph;
    std::shared_ptr<weighted_tree> spanningTree;
    int expectedMinCut;

    input_graph make_copy();
};

input_graph read_form_in(std::istream& in);

}  // namespace examples

#endif /* INPUT_GRAPH_H */
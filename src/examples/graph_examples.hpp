#ifndef GRAPH_EXAMPLES_H
#define GRAPH_EXAMPLES_H
#include <memory>

#include "../graphs/undirected_weighted_graph.hpp"
#include "../graphs/weighted_tree.hpp"
#include "input_graph.hpp"

namespace examples {
using namespace graphs;

input_graph get_example(int nr);

}  // namespace examples
#endif /* GRAPH_EXAMPLES_H */
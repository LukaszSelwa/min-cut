#include "algo.hpp"

algo::algo(std::shared_ptr<graphs::weighted_graph> graph,
           std::shared_ptr<graphs::weighted_tree> tree)
    : graph(graph), tree(tree) {}
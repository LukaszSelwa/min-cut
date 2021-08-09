#ifndef RANDOM_SPANNING_TREES_EXTRACTOR
#define RANDOM_SPANNING_TREES_EXTRACTOR
#include <memory>
#include <random>
#include <vector>

#include "../graphs/undirected_weighted_graph.hpp"
#include "../graphs/weighted_tree.hpp"

graphs::weighted_tree extractSingleRandomSpanningTree(graphs::weighted_graph& graph,
                                                      std::shared_ptr<std::mt19937> seed);

std::shared_ptr<graphs::weighted_tree> extractSingleRandomWeightedSpanningTree(
    std::shared_ptr<graphs::weighted_graph> graph, std::shared_ptr<std::mt19937> seed);

std::vector<graphs::weighted_tree> extractRandomSpanningTrees(graphs::weighted_graph& graph,
                                                              std::shared_ptr<std::mt19937> seed);

#endif /* RANDOM_SPANNING_TREES_EXTRACTOR */
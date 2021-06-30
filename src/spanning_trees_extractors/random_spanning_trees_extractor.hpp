#ifndef RANDOM_SPANNING_TREES_EXTRACTOR
#define RANDOM_SPANNING_TREES_EXTRACTOR
#include <memory>
#include <random>
#include <vector>
#include "../graphs/undirected_weighted_graph.hpp"
#include "../graphs/weighted_tree.hpp"

graphs::WeightedTree extractSingleRandomSpanningTree (graphs::weighted_graph & graph, std::shared_ptr<std::mt19937> seed);
std::vector<graphs::WeightedTree> extractRandomSpanningTrees (graphs::weighted_graph & graph,  std::shared_ptr<std::mt19937> seed);

#endif /* RANDOM_SPANNING_TREES_EXTRACTOR */
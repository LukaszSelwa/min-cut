#ifndef RANDOM_SPANNING_TREES_EXTRACTOR
#define RANDOM_SPANNING_TREES_EXTRACTOR
#include <vector>
#include "../graphs/undirected_weighted_graph.hpp"
#include "../graphs/weighted_tree.hpp"

std::vector<graphs::WeightedTree> extractRandomSpanningTrees (graphs::UndirectedWeightedGraph & graph);

#endif /* RANDOM_SPANNING_TREES_EXTRACTOR */
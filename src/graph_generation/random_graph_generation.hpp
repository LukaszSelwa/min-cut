#ifndef RANDOM_GRAPH_GENERATION_H
#define RANDOM_GRAPH_GENERATION_H
#include <memory>
#include <random>
#include <vector>

#include "../graphs/undirected_weighted_graph.hpp"
#include "../utils/types.hpp"
namespace graphs {
/**
 * Generates random graph with n nodes and m edges in O(n^2) time.
 * @n - should be positive integer
 * @m - should be in range [n-1, n(n-1)/2]
 */
std::shared_ptr<graphs::weighted_graph> generate_random_graph(size_t n, size_t m, int maxWeight,
                                                              std::shared_ptr<std::mt19937> seed);

std::shared_ptr<graphs::weighted_graph> generate_random_graph(std::vector<bool> cut, int cutVal,
                                                              size_t cutEdges,
                                                              size_t nrSpanningTrees,
                                                              std::shared_ptr<std::mt19937> seed);

algo_input generate_random_graph_input(size_t size, size_t cutSize, size_t cutEdges,
                                       size_t nrSpanningTrees, int cutVal,
                                       std::shared_ptr<std::mt19937> seed);

algo_input generate_fully_random_graph_input(size_t minSize, size_t maxSize, size_t maxCutVal,
                                             size_t minNrSpanningTrees, size_t maxNrSpanningTrees,
                                             std::shared_ptr<std::mt19937> seed, int type = -1);

}  // namespace graphs

#endif /* RANDOM_GRAPH_GENERATION_H */
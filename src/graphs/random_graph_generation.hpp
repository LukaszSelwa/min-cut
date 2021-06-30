#ifndef RANDOM_GRAPH_GENERATION_H
#define RANDOM_GRAPH_GENERATION_H
#include <memory>
#include <random>
#include "undirected_weighted_graph.hpp"
namespace graphs {
/**
 * Generates random graph with n nodes and m edges in O(n^2) time.
 * @n - should be positive integer
 * @m - should be in range [n-1, n(n-1)/2]
 */
std::shared_ptr<graphs::weighted_graph> generate_random_graph(size_t n, size_t m, int maxWeight, std::shared_ptr<std::mt19937> seed);

}

#endif /* RANDOM_GRAPH_GENERATION_H */
#ifndef GRAPH_GENERATION__EDGE_CASES_H
#define GRAPH_GENERATION__EDGE_CASES_H
#include <memory>

#include "../graphs/undirected_weighted_graph.hpp"

std::shared_ptr<graphs::weighted_graph> generate_ladder_graph(size_t height, int edgeWeight,
                                                              int levelWeight);

#endif /* GRAPH_GENERATION__EDGE_CASES_H */
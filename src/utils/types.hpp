#ifndef UTILS_TYPES_H
#define UTILS_TYPES_H
#include <memory>
#include <vector>

#include "../graphs/undirected_weighted_graph.hpp"

struct algo_result {
    int minCutVal;
    std::vector<bool> cut;
};

struct algo_input {
    std::shared_ptr<graphs::weighted_graph> graph;
    std::vector<bool> minCut;
    int minCutVal;
};

bool validate_cuts(const std::vector<bool>& cutA, const std::vector<bool>& cutB);

#endif /* UTILS_TYPES_H */
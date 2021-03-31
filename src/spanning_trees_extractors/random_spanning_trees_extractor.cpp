#include "random_spanning_trees_extractor.hpp"

/* resturns approximately 2 * log_2(graphSize) */
size_t calcNumberOfSpanningTrees (size_t graphSize) {
    size_t result = 1;
    while (graphSize > 0) {
        result += 2;
        graphSize = graphSize << 1;
    }
    return result;
}

std::vector<graphs::UndirectedWeightedGraph> extractRandomSpanningTrees (graphs::UndirectedWeightedGraph graph) {
    std::vector<graphs::UndirectedWeightedGraph> trees_list(0);

    return trees_list;
}
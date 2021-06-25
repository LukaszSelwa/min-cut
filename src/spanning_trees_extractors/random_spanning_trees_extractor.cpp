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

graphs::WeightedTree GenerateRandomSpanningTree (const graphs::UndirectedWeightedGraph & graph) {
    int n = graph.GetSize();
    graphs::WeightedTree spanningTree(n);
    std::vector<bool> connected(n, false);


    return spanningTree;
}

std::vector<graphs::WeightedTree> extractRandomSpanningTrees (graphs::UndirectedWeightedGraph & graph) {
    int numberOfTrees = calcNumberOfSpanningTrees(graph.GetSize());
    std::vector<graphs::WeightedTree> trees_list(numberOfTrees);
    for (auto & tree : trees_list)
        tree = GenerateRandomSpanningTree(graph);
    return trees_list;
}
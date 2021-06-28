#include "random_spanning_trees_extractor.hpp"
#include "../helper_funcs/random_queue.hpp"

/* resturns approximately 2 * log_2(graphSize) */
size_t calcNumberOfSpanningTrees (size_t graphSize) {
    size_t result = 1;
    while (graphSize > 0) {
        result += 2;
        graphSize = graphSize << 1;
    }
    return result;
}

graphs::WeightedTree extractSingleRandomSpanningTree (graphs::UndirectedWeightedGraph & graph, std::shared_ptr<std::mt19937> seed) {
    int n = graph.GetSize();
    graphs::WeightedTree spanning_tree(n);
    std::vector<bool> connected(n, false);
    RandomQueue<graphs::WeightedEdge> rq(seed);

    connected[0] = true;
    for (auto edge : graph[0].GetNeighbors())
        rq.push(edge);

    while (!rq.empty()) {
        auto edge = rq.pop();
        if (connected[edge.destIdx])
            continue;
        connected[edge.destIdx] = true;
        spanning_tree.AddEdge(edge.srcIdx, edge.destIdx, edge.weight);
        for (auto & e : graph[edge.destIdx].GetNeighbors()) {
            if (!connected[e.destIdx])
                rq.push(e);
        }
    }
    
    return spanning_tree;
}

std::vector<graphs::WeightedTree> extractRandomSpanningTrees (graphs::UndirectedWeightedGraph & graph, std::shared_ptr<std::mt19937> seed) {
    int numberOfTrees = calcNumberOfSpanningTrees(graph.GetSize());
    std::vector<graphs::WeightedTree> trees_list(numberOfTrees);
    for (auto & tree : trees_list)
        tree = extractSingleRandomSpanningTree(graph, seed);
    return trees_list;
}
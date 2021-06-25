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

graphs::WeightedTree GenerateRandomSpanningTree (graphs::UndirectedWeightedGraph & graph) {
    int n = graph.GetSize();
    graphs::WeightedTree spanningTree(n);
    std::vector<bool> connected(n, false);
    RandomQueue<graphs::WeightedEdge> rq(0);

    connected[0] = true;
    for (auto edge : graph[0].GetNeighbors())
        rq.push(edge);

    while (!rq.empty()) {
        auto edge = rq.pop();
        if (connected[edge.destIdx])
            continue;
        connected[edge.destIdx] = true;
        spanningTree.AddEdge(edge.srcIdx, edge.destIdx, edge.weight);
        for (auto & e : graph[edge.destIdx].GetNeighbors()) {
            if (!connected[e.destIdx])
                rq.push(e);
        }
    }
    
    return spanningTree;
}

std::vector<graphs::WeightedTree> extractRandomSpanningTrees (graphs::UndirectedWeightedGraph & graph) {
    int numberOfTrees = calcNumberOfSpanningTrees(graph.GetSize());
    std::vector<graphs::WeightedTree> trees_list(numberOfTrees);
    for (auto & tree : trees_list)
        tree = GenerateRandomSpanningTree(graph);
    return trees_list;
}
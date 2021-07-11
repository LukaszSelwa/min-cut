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

graphs::weighted_tree extractSingleRandomSpanningTree (graphs::weighted_graph & graph, std::shared_ptr<std::mt19937> seed) {
    int n = graph.size;
    graphs::weighted_tree spanning_tree(n);
    std::vector<bool> connected(n, false);
    RandomQueue<graphs::w_edge> rq(seed);

    connected[0] = true;
    for (auto edge : graph[0].neighbors)
        rq.push(edge);

    while (!rq.empty()) {
        auto edge = rq.pop();
        if (connected[edge.destIdx])
            continue;
        connected[edge.destIdx] = true;
        spanning_tree.add_child_edge(edge.srcIdx, edge.destIdx, edge.weight);
        for (auto & e : graph[edge.destIdx].neighbors) {
            if (!connected[e.destIdx])
                rq.push(e);
        }
    }
    
    return spanning_tree;
}

std::vector<graphs::weighted_tree> extractRandomSpanningTrees (graphs::weighted_graph & graph, std::shared_ptr<std::mt19937> seed) {
    int numberOfTrees = calcNumberOfSpanningTrees(graph.size);
    std::vector<graphs::weighted_tree> trees_list(numberOfTrees);
    for (auto & tree : trees_list)
        tree = extractSingleRandomSpanningTree(graph, seed);
    return trees_list;
}
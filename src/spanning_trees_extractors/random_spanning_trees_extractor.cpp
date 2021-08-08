#include "random_spanning_trees_extractor.hpp"

#include <functional>

#include "../utils/find_union.hpp"
#include "../utils/random_queue.hpp"
#include "../utils/random_weighted_queue.hpp"

/* resturns approximately 2 * log_2(graphSize) */
size_t calcNumberOfSpanningTrees(size_t graphSize) {
    size_t result = 1;
    while (graphSize > 0) {
        result += 2;
        graphSize = graphSize << 1;
    }
    return result;
}

graphs::weighted_tree extractSingleRandomSpanningTree(graphs::weighted_graph& graph,
                                                      std::shared_ptr<std::mt19937> seed) {
    int n = graph.size;
    graphs::weighted_tree spanning_tree(n);
    std::vector<bool> connected(n, false);
    RandomQueue<graphs::w_edge> rq(seed);

    connected[0] = true;
    for (auto edge : graph[0].neighbors) rq.push(edge);

    while (!rq.empty()) {
        auto edge = rq.pop();
        if (connected[edge.destIdx]) continue;
        connected[edge.destIdx] = true;
        spanning_tree.add_child_edge(edge.srcIdx, edge.destIdx, edge.weight);
        for (auto& e : graph[edge.destIdx].neighbors) {
            if (!connected[e.destIdx]) rq.push(e);
        }
    }

    return spanning_tree;
}

std::shared_ptr<graphs::weighted_tree> extractSingleRandomWeightedSpanningTree(
    std::shared_ptr<graphs::weighted_graph> graph, std::mt19937 seed) {
    int n = graph->size;
    graphs::weighted_graph treeGraph(n);
    auto spanningTree = std::make_shared<graphs::weighted_tree>(n);

    std::vector<graphs::w_edge> edges(0);
    std::vector<int> weights(0);

    for (auto& v : graph->vertices) {
        for (auto& e : v.neighbors) {
            if (e.srcIdx < e.destIdx) {
                edges.push_back(e);
                weights.push_back(e.weight);
            }
        }
    }

    random_weighted_queue<graphs::w_edge> rq(seed);
    rq.initialize(edges, weights);
    find_union fu(n);

    while (fu.get_max_cluster_size() < n) {
        auto ed = rq.pop();
        if (!fu.are_united(ed.srcIdx, ed.destIdx)) {
            treeGraph.add_edge(ed);
            fu.unite(ed.srcIdx, ed.destIdx);
        }
    }

    std::function<void(int, int)> dfs = [&](int idx, int parentIdx) {
        for (auto& ed : treeGraph.vertices[idx].neighbors) {
            if (ed.destIdx != parentIdx) {
                spanningTree->add_child_edge(ed.srcIdx, ed.destIdx, ed.weight);
                dfs(ed.destIdx, idx);
            }
        }
    };

    dfs(0, -1);

    return spanningTree;
}

std::vector<graphs::weighted_tree> extractRandomSpanningTrees(graphs::weighted_graph& graph,
                                                              std::shared_ptr<std::mt19937> seed) {
    int numberOfTrees = calcNumberOfSpanningTrees(graph.size);
    std::vector<graphs::weighted_tree> trees_list(numberOfTrees);
    for (auto& tree : trees_list) tree = extractSingleRandomSpanningTree(graph, seed);
    return trees_list;
}
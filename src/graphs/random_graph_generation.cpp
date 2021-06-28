#include "undirected_weighted_graph.hpp"
#include "../helper_funcs/random_queue.hpp"

namespace graphs {

std::shared_ptr<graphs::UndirectedWeightedGraph> generateRandomGraph(size_t n, size_t m, int max_weight, std::shared_ptr<std::mt19937> seed) {
    std::shared_ptr<graphs::UndirectedWeightedGraph> graph(new graphs::UndirectedWeightedGraph(n));
    std::uniform_int_distribution<> dist_weight(0, max_weight);
    std::vector<std::vector<bool> > adj_mtx(n, std::vector<bool>(n, false));
    
    // generate random connected tree inside graph
    RandomQueue<int> connected(seed);
    RandomQueue<int> disconnected(seed);
    for (int i = 0; i < n; ++i)
        disconnected.push(i);
    connected.push(disconnected.pop());
    while (!disconnected.empty()) {
        int x = connected.pop();
        int y = disconnected.pop();
        graph->AddEdge(graphs::WeightedEdge(x, y, dist_weight(*seed)));
        adj_mtx[x][y] = adj_mtx[y][x] = true;
        connected.push(x);
        connected.push(y);
    }

    // list possible unused edges
    RandomQueue<graphs::WeightedEdge> pos_edges(seed);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (!adj_mtx[i][j])
                pos_edges.push(graphs::WeightedEdge(i, j, dist_weight(*seed)));
        }
    }

    // add left edges
    m = m - (n-1);
    while (m > 0 && !pos_edges.empty()) {
        graph->AddEdge(pos_edges.pop());
        m--;
    }
    return graph;
}

}
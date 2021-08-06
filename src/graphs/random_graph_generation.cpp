#include "../utils/random_queue.hpp"
#include "undirected_weighted_graph.hpp"

namespace graphs {

std::shared_ptr<graphs::weighted_graph> generate_random_graph(size_t n, size_t m, int maxWeight,
                                                              std::shared_ptr<std::mt19937> seed) {
    std::shared_ptr<graphs::weighted_graph> graph(new graphs::weighted_graph(n));
    std::uniform_int_distribution<> distWeight(0, maxWeight);
    std::vector<std::vector<bool> > adjMtx(n, std::vector<bool>(n, false));

    // generate random connected tree inside graph
    RandomQueue<int> connected(seed);
    RandomQueue<int> disconnected(seed);
    for (int i = 0; i < n; ++i) disconnected.push(i);
    connected.push(disconnected.pop());
    while (!disconnected.empty()) {
        int x = connected.pop();
        int y = disconnected.pop();
        graph->add_edge(graphs::w_edge(x, y, distWeight(*seed)));
        adjMtx[x][y] = adjMtx[y][x] = true;
        connected.push(x);
        connected.push(y);
    }

    // list possible unused edges
    RandomQueue<graphs::w_edge> posEdges(seed);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (!adjMtx[i][j]) posEdges.push(graphs::w_edge(i, j, distWeight(*seed)));
        }
    }

    // add left edges
    m = m - (n - 1);
    while (m > 0 && !posEdges.empty()) {
        graph->add_edge(posEdges.pop());
        m--;
    }
    return graph;
}

}  // namespace graphs
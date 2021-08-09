#include "random_graph_generation.hpp"

#include <algorithm>

#include "../graphs/undirected_weighted_graph.hpp"
#include "../utils/random_queue.hpp"

namespace graphs {

std::vector<int> divide_int(int val, size_t elements, std::shared_ptr<std::mt19937> seed);

void add_random_spanning_tree(std::vector<int> vertices, std::vector<std::vector<int>>& mtx,
                              int minWeight, int maxWeight, std::shared_ptr<std::mt19937> seed);

std::shared_ptr<graphs::weighted_graph> generate_random_graph(size_t n, size_t m, int maxWeight,
                                                              std::shared_ptr<std::mt19937> seed) {
    std::shared_ptr<graphs::weighted_graph> graph(new graphs::weighted_graph(n));
    std::uniform_int_distribution<> distWeight(1, maxWeight);
    std::vector<std::vector<bool>> adjMtx(n, std::vector<bool>(n, false));

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

std::shared_ptr<graphs::weighted_graph> generate_random_graph(std::vector<bool> cut, int cutVal,
                                                              size_t cutEdges,
                                                              size_t nrSpanningTrees,
                                                              std::shared_ptr<std::mt19937> seed) {
    size_t n = cut.size();
    auto graph = std::make_shared<weighted_graph>(n);

    std::vector<int> cutTrue(0), cutFalse(0);
    for (int i = 0; i < n; ++i) {
        if (cut[i])
            cutTrue.push_back(i);
        else
            cutFalse.push_back(i);
    }

    std::vector<std::vector<int>> mtx(n, std::vector<int>(n, 0));

    {  // add cut edges
        RandomQueue<std::pair<int, int>> rq_edges(seed);
        for (int v : cutTrue) {
            for (int w : cutFalse) rq_edges.push(std::pair<int, int>(v, w));
        }

        auto weights = divide_int(cutVal, cutEdges, seed);
        for (int w : weights) {
            auto e = rq_edges.pop();
            mtx[e.first][e.second] += w;
            mtx[e.second][e.first] += w;
        }
    }

    int minWeight = (cutVal + nrSpanningTrees - 1) / nrSpanningTrees;
    int maxWeight = (3 * minWeight + 1) / 2;

    for (size_t itr = 0; itr < nrSpanningTrees; ++itr) {
        add_random_spanning_tree(cutTrue, mtx, minWeight, maxWeight, seed);
        add_random_spanning_tree(cutFalse, mtx, minWeight, maxWeight, seed);
    }

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < x; ++y) {
            if (mtx[x][y] > 0) graph->add_edge(w_edge(x, y, mtx[x][y]));
        }
    }

    return graph;
}

std::vector<int> divide_int(int val, size_t elements, std::shared_ptr<std::mt19937> seed) {
    std::vector<int> result(elements, 0);
    std::vector<int> breakpoints(elements - 1, 0);
    std::uniform_int_distribution<int> dist(0, val - elements);

    for (auto& b : breakpoints) b = dist(*seed);
    std::sort(breakpoints.begin(), breakpoints.end());

    int prev = 0;
    for (int i = 0; i < elements - 1; ++i) {
        result[i] = breakpoints[i] - prev + 1;
        prev = breakpoints[i];
    }
    result.back() = val - elements - prev + 1;
    return result;
}

void add_random_spanning_tree(std::vector<int> vertices, std::vector<std::vector<int>>& mtx,
                              int minWeight, int maxWeight, std::shared_ptr<std::mt19937> seed) {
    std::uniform_int_distribution<> distWeight(minWeight, maxWeight);
    RandomQueue<int> connected(seed);
    RandomQueue<int> disconnected(seed);
    for (int v : vertices) disconnected.push(v);
    connected.push(disconnected.pop());
    while (!disconnected.empty()) {
        int x = connected.pop();
        int y = disconnected.pop();
        int w = distWeight(*seed);
        mtx[x][y] += w;
        mtx[y][x] += w;
        connected.push(x);
        connected.push(y);
    }
}

}  // namespace graphs
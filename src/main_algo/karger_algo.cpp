#include "karger_algo.hpp"

karger_algo::karger_algo(std::shared_ptr<graphs::weighted_graph> graph,
                         std::shared_ptr<graphs::weighted_tree> tree)
    : graph(graph), tree(tree), lca(tree) {}

void karger_algo::initialize() {
    n = tree->size;
    lca.initialize();

    rho = subtreeCost = std::vector<int>(n, 0);
    calc_subtree_cost();
    calc_rho();

    pairCost = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
    calc_pair_cost();
}

void karger_algo::calc_rho() {
    for (auto& v : graph->vertices) {
        for (auto& ed : v.neighbors) {
            rho[lca.calc_lca(ed.srcIdx, ed.destIdx)] += ed.weight;
        }
    }
    tree->run_postorder([&](graphs::tree_vertice& v) {
        for (auto& e : v.children) {
            rho[v.idx] += rho[e.destIdx];
        }
    });
}

void karger_algo::calc_subtree_cost() {
    for (auto& v : graph->vertices) {
        for (auto& ed : v.neighbors) {
            subtreeCost[v.get_idx()] += ed.weight;
            subtreeCost[lca.calc_lca(ed.srcIdx, ed.destIdx)] -= ed.weight;
        }
    }

    tree->run_postorder([&](graphs::tree_vertice& v) {
        for (auto& e : v.children) {
            subtreeCost[v.idx] += subtreeCost[e.destIdx];
        }
    });
}

void karger_algo::calc_pair_cost() {
    for (size_t vIdx = 0; vIdx < n; ++vIdx) {
        auto& vCost = pairCost[vIdx];
        for (auto& e : graph->vertices[vIdx].neighbors) {
            vCost[e.destIdx] = e.weight;
        }

        tree->run_postorder([&](graphs::tree_vertice& w) {
            for (auto& e : w.children) {
                vCost[w.idx] += vCost[e.destIdx];
            }
        });
    }
    for (size_t wIdx = 0; wIdx < n; ++wIdx) {
        tree->run_postorder([&](graphs::tree_vertice& v) {
            for (auto& e : v.children) {
                pairCost[v.idx][wIdx] += pairCost[e.destIdx][wIdx];
            }
        });
    }
}

int karger_algo::get_cut_val(int v, int w) {
    int l = lca.calc_lca(v, w);
    if (v == w) {
        return subtreeCost[v];
    } else if (l == w) {
        return subtreeCost[w] - subtreeCost[v] + 2 * (pairCost[v][w] - rho[v]);
    } else if (l == v) {
        return subtreeCost[v] - subtreeCost[w] + 2 * (pairCost[w][v] - rho[w]);
    } else {
        return subtreeCost[v] + subtreeCost[w] - 2 * pairCost[v][w];
    }
}

edge_pair karger_algo::find_cut() {
    edge_pair result{.val = std::numeric_limits<int>::max()};
    for (size_t vIdx = 0; vIdx < n; ++vIdx) {
        if (vIdx == tree->rootIdx) continue;
        for (size_t wIdx = 0; wIdx < n; ++wIdx) {
            if (wIdx == tree->rootIdx) continue;
            result = std::min(result, edge_pair{
                                          .e1 = tree->vertices[vIdx].parentEdge,
                                          .e2 = tree->vertices[wIdx].parentEdge,
                                          .val = get_cut_val(vIdx, wIdx),
                                      });
        }
    }
    return result;
}
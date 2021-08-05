#ifndef KARGER_ALGO_H
#define KARGER_ALGO_H
#include <memory>
#include <vector>

#include "../graphs/lca_computer.hpp"
#include "../graphs/undirected_weighted_graph.hpp"
#include "../graphs/weighted_tree.hpp"
#include "common.hpp"

class karger_algo {
   private:
    std::shared_ptr<graphs::weighted_graph> graph;
    std::shared_ptr<graphs::weighted_tree> tree;
    size_t n;
    graphs::lca_computer lca;
    void calc_subtree_cost();
    void calc_pair_cost();
    void calc_rho();

   public:
    std::vector<int> rho;
    std::vector<int> subtreeCost;
    std::vector<std::vector<int>> pairCost;
    karger_algo(std::shared_ptr<graphs::weighted_graph> graph,
                std::shared_ptr<graphs::weighted_tree> tree);
    void initialize();
    int get_cut_val(int v, int w);
    edge_pair find_cut();
};

#endif /* KARGER_ALGO_H */
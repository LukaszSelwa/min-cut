#ifndef ALGO_H
#define ALGO_H
#include <memory>

#include "../graphs/binarized_tree.hpp"
#include "../graphs/gmw_structure.hpp"
#include "../graphs/hl_decomposition.hpp"
#include "../graphs/undirected_weighted_graph.hpp"
#include "../graphs/weighted_tree.hpp"
#include "../range_search/interval2D_tree.hpp"

struct edge_pair {
    graphs::w_edge e1, e2;
    int val;
};

const graphs::w_edge NIL_EDGE(-1, -1);

class algo {
   private:
    std::shared_ptr<graphs::weighted_graph> graph;
    std::shared_ptr<graphs::weighted_tree> tree;

   public:
    std::shared_ptr<gmw_structure> gmw;
    std::shared_ptr<graphs::hl_decomposition> hld;
    algo(std::shared_ptr<graphs::weighted_graph> graph,
         std::shared_ptr<graphs::weighted_tree> tree);
    void initialize_structures();
    edge_pair find_1respect_cut();
    edge_pair find_2respect_cut_in_single_hl_path(int pathIdx);
};

#endif /* ALGO_H */
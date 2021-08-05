#ifndef GMW_ALGO_H
#define GMW_ALGO_H
#include <memory>

#include "../graphs/binarized_tree.hpp"
#include "../graphs/gmw_structure.hpp"
#include "../graphs/hl_decomposition.hpp"
#include "../graphs/undirected_weighted_graph.hpp"
#include "../graphs/weighted_tree.hpp"
#include "../range_search/segment_2d_point_tree.hpp"
#include "common.hpp"

class gmw_algo {
   private:
    std::shared_ptr<graphs::weighted_graph> graph;
    std::shared_ptr<graphs::weighted_tree> tree;

   public:
    std::shared_ptr<gmw_structure> gmw;
    std::shared_ptr<graphs::hl_decomposition> hld;
    gmw_algo(std::shared_ptr<graphs::weighted_graph> graph,
             std::shared_ptr<graphs::weighted_tree> tree);
    void initialize();
    edge_pair find_1respect_cut();
    edge_pair find_2respect_cut_single(int pathIdx);
    edge_pair find_2respect_cut_single();
    edge_pair find_2respect_cut_pair(graphs::interested_path_pair& paths);
    edge_pair find_2respect_cut_pair();
    edge_pair find_cut();
};

#endif /* GMW_ALGO_H */
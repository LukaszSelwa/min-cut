#ifndef HEURISTIC_ALGO_H
#define HEURISTIC_ALGO_H
#include <memory>
#include <random>

#include "../graphs/undirected_weighted_graph.hpp"
#include "../graphs/weighted_tree.hpp"
#include "../utils/types.hpp"
#include "common.hpp"

namespace heuristic {
class algo {
    std::shared_ptr<graphs::weighted_graph> graph;
    size_t get_iterations_nr();
    algo_result run_iteration(std::shared_ptr<std::mt19937> seed);
    std::vector<bool> get_cut(std::shared_ptr<graphs::weighted_tree> tree, edge_pair cut2respect);

   public:
    algo(std::shared_ptr<graphs::weighted_graph> graph);
    algo_result calc_min_cut();
};
}  // namespace heuristic

#endif /* HEURISTIC_ALGO_H */
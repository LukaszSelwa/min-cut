#ifndef NAIVE_ALGO_H
#define NAIVE_ALGO_H
#include <memory>

#include "../graphs/undirected_weighted_graph.hpp"
#include "../utils/types.hpp"
#include "flow_graph.hpp"

namespace naive {
class algo {
    std::shared_ptr<graphs::weighted_graph> graph;
    flow_graph fg;
    void translate_graph();

   public:
    algo(std::shared_ptr<graphs::weighted_graph> graph);
    algo_result calc_min_cut();
};
}  // namespace naive

#endif /* NAIVE_ALGO_H */
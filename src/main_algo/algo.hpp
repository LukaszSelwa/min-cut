#ifndef ALGO_H
#define ALGO_H
#include <memory>

#include "../graphs/undirected_weighted_graph.hpp"
#include "../graphs/weighted_tree.hpp"

class algo {
   private:
    std::shared_ptr<graphs::weighted_graph> graph;
    std::shared_ptr<graphs::weighted_tree> tree;

   public:
    algo(std::shared_ptr<graphs::weighted_graph> graph,
         std::shared_ptr<graphs::weighted_tree> tree);
    void initialize_structures();
};

#endif /* ALGO_H */
#ifndef MN_STRUCTURE_H
#define MN_STRUCTURE_H
#include <memory>
#include <vector>
#include "lca_computer.hpp"
#include "undirected_weighted_graph.hpp"
#include "weighted_tree.hpp"
#include "../range_search/range_search_structure.cpp"

class gmw_structure {
    std::unique_ptr<RangeSearchStructure> rs;
    std::vector<int> subtreeCost;
    std::vector<int> postorderVisit;
    std::vector<int> subtreePostorderVisit;
    int n;

    int get_lower_endpoint(graphs::WeightedEdge e);
    bool is_descendant(int u, int v);
    int get_independent_cost(int u, int v);
    int get_descendant_cost(int u, int v);
    
  public:
    gmw_structure(std::unique_ptr<RangeSearchStructure> rs);
    void initialize(std::shared_ptr<graphs::weighted_graph> graph, std::shared_ptr<graphs::WeightedTree> tree);
    int get_cut_val(graphs::WeightedEdge e1, graphs::WeightedEdge e2);
    bool is_crossinterested(graphs::WeightedEdge e1, graphs::WeightedEdge e2);
    bool is_downinterested(graphs::WeightedEdge e1, graphs::WeightedEdge e2);

    // for testing
    std::vector<int> get_subtree_cost() { return subtreeCost; }
    std::vector<int> get_postorder_visit() { return postorderVisit; }
    std::vector<int> get_subtree_postorder_visit() { return subtreePostorderVisit; }
};

#endif /* MN_STRUCTURE_H */
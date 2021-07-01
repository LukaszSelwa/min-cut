#ifndef MN_STRUCTURE_H
#define MN_STRUCTURE_H
#include <memory>
#include <vector>
#include "lca_computer.hpp"
#include "undirected_weighted_graph.hpp"
#include "weighted_tree.hpp"
#include "../range_search/range_search_structure.cpp"

struct postord_range{
    int begin, end;
    friend bool operator== (const postord_range & pr1, const postord_range & pr2) {
        return pr1.begin == pr2.begin && pr1.end == pr1.end;
    }
    bool contains(int x);
};

class gmw_structure {
    std::unique_ptr<RangeSearchStructure> rs;
    int n;

    bool is_descendant(int u, int v);
    int get_descendant_cost(int u, int v);
    int get_independent_cost(int u, int v);
    
  public:
    gmw_structure(std::unique_ptr<RangeSearchStructure> rs);
    bool is_crossinterested(graphs::WeightedEdge e1, graphs::WeightedEdge e2);
    bool is_crossinterested(int idx, postord_range pr);
    bool is_downinterested(graphs::WeightedEdge e1, graphs::WeightedEdge e2);
    bool is_downinterested(int idx, postord_range pr);
    int get_cut_val(graphs::WeightedEdge e1, graphs::WeightedEdge e2);
    int get_lower_endpoint(graphs::WeightedEdge e);
    void initialize(std::shared_ptr<graphs::weighted_graph> graph, std::shared_ptr<graphs::WeightedTree> tree);

    std::vector<int> subtreeCost;
    std::vector<postord_range> postorder;
};

#endif /* MN_STRUCTURE_H */
#ifndef MN_STRUCTURE_H
#define MN_STRUCTURE_H
#include <memory>
#include <vector>

#include "../range_search/range_search_structure.cpp"
#include "lca_computer.hpp"
#include "undirected_weighted_graph.hpp"
#include "weighted_tree.hpp"

struct postord_range {
    int begin, end;
    friend bool operator==(const postord_range& pr1, const postord_range& pr2) {
        return pr1.begin == pr2.begin && pr1.end == pr2.end;
    }
    bool contains(int x);
};

class gmw_structure {
    std::unique_ptr<RangeSearchStructure> rs;
    int n;

    int get_descendant_cost(int u, int v);
    int get_independent_cost(int u, int v);

   public:
    gmw_structure(std::unique_ptr<RangeSearchStructure> rs);
    bool are_independent(int u, int v);
    bool is_crossinterested(graphs::w_edge e1, graphs::w_edge e2);
    bool is_crossinterested(int idx, postord_range pr);
    bool is_descendant(int u, int v);
    bool is_downinterested(graphs::w_edge e1, graphs::w_edge e2);
    bool is_downinterested(int idx, postord_range pr);
    int get_cut_val(graphs::w_edge e1, graphs::w_edge e2);
    int get_lower_endpoint(graphs::w_edge e);
    void initialize(std::shared_ptr<graphs::weighted_graph> graph,
                    std::shared_ptr<graphs::weighted_tree> tree);

    std::vector<int> subtreeCost;
    std::vector<postord_range> postorder;
};

#endif /* MN_STRUCTURE_H */
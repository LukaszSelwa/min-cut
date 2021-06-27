#ifndef MN_STRUCTURE_H
#define MN_STRUCTURE_H
#include <memory>
#include <vector>
#include "lca_computer.hpp"
#include "undirected_weighted_graph.hpp"
#include "weighted_tree.hpp"
#include "../range_search/range_search_structure.cpp"

class GMWStructure {
    std::unique_ptr<RangeSearchStructure> rs;
    std::vector<int> subtree_cost;
    std::vector<int> postorder_visit;
    std::vector<int> subtree_postorder_visit;
    int n;

    int GetLowerEndpoint(graphs::WeightedEdge e);
    bool IsDescendant(int u, int v);
    int GetIndependentCost(int u, int v);
    int GetDescendantCost(int u, int v);
    
  public:
    GMWStructure(std::unique_ptr<RangeSearchStructure> rs);
    void Initialize(std::shared_ptr<graphs::UndirectedWeightedGraph> graph, std::shared_ptr<graphs::WeightedTree> tree);
    int GetCutVal(graphs::WeightedEdge e1, graphs::WeightedEdge e2);
    bool IsCrossInterested(graphs::WeightedEdge e1, graphs::WeightedEdge e2);
    bool IsDownInterested(graphs::WeightedEdge e1, graphs::WeightedEdge e2);

    // for testing
    std::vector<int> GetSubtreeCost() { return subtree_cost; }
    std::vector<int> GetPostorderVisit() { return postorder_visit; }
    std::vector<int> GetSubtreePostorderVisit() { return subtree_postorder_visit; }
};

#endif /* MN_STRUCTURE_H */
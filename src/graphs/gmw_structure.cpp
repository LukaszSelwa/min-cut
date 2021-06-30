#include "gmw_structure.hpp"
#include <algorithm>

int calc_cost_bottomup(std::shared_ptr<graphs::WeightedTree> &tree,
                     std::vector<int> &delta,
                     std::vector<int> &cost,
                     int idx,
                     int p_idx);

int gmw_structure::get_lower_endpoint(graphs::WeightedEdge e) {
    return postorderVisit[e.srcIdx] < postorderVisit[e.destIdx] ? e.srcIdx : e.destIdx;
}

bool gmw_structure::is_descendant(int u, int v) {
    return subtreePostorderVisit[u] <= postorderVisit[v] && postorderVisit[v] <= postorderVisit[u];
}

int gmw_structure::get_independent_cost(int u, int v) {
    return rs->GetSumInRectangle(
        subtreePostorderVisit[u], postorderVisit[u],
        subtreePostorderVisit[v], postorderVisit[v]
    );
}
int gmw_structure::get_descendant_cost(int u, int v) {
    return rs->GetSumInRectangle(
        subtreePostorderVisit[v], postorderVisit[v],
        1, subtreePostorderVisit[u]-1
    ) + rs->GetSumInRectangle(
        subtreePostorderVisit[v], postorderVisit[v],
        postorderVisit[u]+1, n
    );
}


gmw_structure::gmw_structure(std::unique_ptr<RangeSearchStructure> rs): rs(std::move(rs)) { }

void gmw_structure::initialize(std::shared_ptr<graphs::weighted_graph> graph, std::shared_ptr<graphs::WeightedTree> tree) {
    graphs::lca_computer lca(tree);
    lca.initialize();
    n = tree->size;
    // Algorithm according to Karger: Minimum Cuts in Near-Linear Time
    // (sum weights of outgoing edges from v_i) - 2 * (sum of edges whose endpoints' lca is v_i)
    std::vector<int> delta(n, 0);
    for (auto & v : graph->vertices) {
        for (auto & ed : v.neighbors) {
            delta[v.GetIdx()] += ed.weight;
            delta[lca.calc_lca(ed.srcIdx, ed.destIdx)] -= ed.weight;
        }
    }
    subtreeCost = postorderVisit = subtreePostorderVisit= std::vector<int>(n, 0);
    calc_cost_bottomup(tree, delta, subtreeCost, tree->rootIdx, -1);
    int nextPostorder = 1;

    tree->RunPostOrder([&](graphs::TreeVertice& v) {
        postorderVisit[v.idx] = nextPostorder++;
        subtreePostorderVisit[v.idx] = postorderVisit[v.idx]; 
        for (auto & ed : v.children) {
            subtreePostorderVisit[v.idx] = std::min(subtreePostorderVisit[ed.destIdx], subtreePostorderVisit[v.idx]);
        }
    });

    for (const auto & v : graph->vertices) {
        for (const auto & ed : v.neighbors) {
            rs->AddPoint(postorderVisit[ed.srcIdx], postorderVisit[ed.destIdx], ed.weight);
        }
    }
}

int gmw_structure::get_cut_val(graphs::WeightedEdge e1, graphs::WeightedEdge e2) {
    // According to Gawrychowski, Mozes, Weimann: A Note on a Recent Algorithm for Minimum Cut
    int u = get_lower_endpoint(e1), v = get_lower_endpoint(e2);
    int w = 0;
    if (is_descendant(u, v))
        w = get_descendant_cost(u, v);
    else if (is_descendant(v, u))
        w = get_descendant_cost(v, u);
    else 
        w = get_independent_cost(u, v);
    return subtreeCost[u] + subtreeCost[v] - 2*w;
}

bool gmw_structure::is_crossinterested(graphs::WeightedEdge e1, graphs::WeightedEdge e2) {
    int u = get_lower_endpoint(e1), v = get_lower_endpoint(e2);
    if (is_descendant(u, v) || is_descendant(v, u))
        return false;
    int w = get_independent_cost(u, v);
    return subtreeCost[u] < subtreeCost[u] + subtreeCost[v] - 2*w;
}

bool gmw_structure::is_downinterested(graphs::WeightedEdge e1, graphs::WeightedEdge e2) {
    int u = get_lower_endpoint(e1), v = get_lower_endpoint(e2);
    if (!is_descendant(u,v))
        return false;
    int w = get_descendant_cost(v, u);
    return subtreeCost[u] < subtreeCost[u] + subtreeCost[v] - 2*w;
}

int calc_cost_bottomup(std::shared_ptr<graphs::WeightedTree> &tree,
                     std::vector<int> &delta,
                     std::vector<int> &cost,
                     int idx,
                     int p_idx) {
    cost[idx] = delta[idx];
    for (auto & ed : tree->vertices[idx].children)
        cost[idx] += calc_cost_bottomup(tree, delta, cost, ed.destIdx, idx);
    cost[idx];
    return cost[idx]; 
}
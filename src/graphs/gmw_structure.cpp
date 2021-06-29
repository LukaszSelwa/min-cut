#include "gmw_structure.hpp"
#include <algorithm>

int CalcCostBottomUp(std::shared_ptr<graphs::WeightedTree> &tree,
                     std::vector<int> &delta,
                     std::vector<int> &cost,
                     int idx,
                     int p_idx);

int GMWStructure::GetLowerEndpoint(graphs::WeightedEdge e) {
    return postorder_visit[e.srcIdx] < postorder_visit[e.destIdx] ? e.srcIdx : e.destIdx;
}

bool GMWStructure::IsDescendant(int u, int v) {
    return subtree_postorder_visit[u] <= postorder_visit[v] && postorder_visit[v] <= postorder_visit[u];
}

int GMWStructure::GetIndependentCost(int u, int v) {
    return rs->GetSumInRectangle(
        subtree_postorder_visit[u], postorder_visit[u],
        subtree_postorder_visit[v], postorder_visit[v]
    );
}
int GMWStructure::GetDescendantCost(int u, int v) {
    return rs->GetSumInRectangle(
        subtree_postorder_visit[v], postorder_visit[v],
        1, subtree_postorder_visit[u]-1
    ) + rs->GetSumInRectangle(
        subtree_postorder_visit[v], postorder_visit[v],
        postorder_visit[u]+1, n
    );
}


GMWStructure::GMWStructure(std::unique_ptr<RangeSearchStructure> rs): rs(std::move(rs)) { }

void GMWStructure::Initialize(std::shared_ptr<graphs::UndirectedWeightedGraph> graph, std::shared_ptr<graphs::WeightedTree> tree) {
    graphs::LCAComputer lca(tree);
    lca.Initialize();
    n = tree->size;
    // Algorithm according to Karger: Minimum Cuts in Near-Linear Time
    // (sum weights of outgoing edges from v_i) - 2 * (sum of edges whose endpoints' lca is v_i)
    std::vector<int> delta(n, 0);
    for (auto & v : graph->vertices) {
        for (auto & ed : v.neighbors) {
            delta[v.GetIdx()] += ed.weight;
            delta[lca.LCA(ed.srcIdx, ed.destIdx)] -= ed.weight;
        }
    }
    subtree_cost = postorder_visit = subtree_postorder_visit= std::vector<int>(n, 0);
    CalcCostBottomUp(tree, delta, subtree_cost, tree->rootIdx, -1);
    int next_postorder = 1;

    tree->RunPostOrder([&](graphs::TreeVertice& v) {
        postorder_visit[v.idx] = next_postorder++;
        subtree_postorder_visit[v.idx] = postorder_visit[v.idx]; 
        for (auto & ed : v.children) {
            subtree_postorder_visit[v.idx] = std::min(subtree_postorder_visit[ed.destIdx], subtree_postorder_visit[v.idx]);
        }
    });

    for (const auto & v : graph->vertices) {
        for (const auto & ed : v.neighbors) {
            rs->AddPoint(postorder_visit[ed.srcIdx], postorder_visit[ed.destIdx], ed.weight);
        }
    }
}

int GMWStructure::GetCutVal(graphs::WeightedEdge e1, graphs::WeightedEdge e2) {
    // According to Gawrychowski, Mozes, Weimann: A Note on a Recent Algorithm for Minimum Cut
    int u = GetLowerEndpoint(e1), v = GetLowerEndpoint(e2);
    int w = 0;
    if (IsDescendant(u, v))
        w = GetDescendantCost(u, v);
    else if (IsDescendant(v, u))
        w = GetDescendantCost(v, u);
    else 
        w = GetIndependentCost(u, v);
    return subtree_cost[u] + subtree_cost[v] - 2*w;
}

bool GMWStructure::IsCrossInterested(graphs::WeightedEdge e1, graphs::WeightedEdge e2) {
    int u = GetLowerEndpoint(e1), v = GetLowerEndpoint(e2);
    if (IsDescendant(u, v) || IsDescendant(v, u))
        return false;
    int w = GetIndependentCost(u, v);
    return subtree_cost[u] < subtree_cost[u] + subtree_cost[v] - 2*w;
}

bool GMWStructure::IsDownInterested(graphs::WeightedEdge e1, graphs::WeightedEdge e2) {
    int u = GetLowerEndpoint(e1), v = GetLowerEndpoint(e2);
    if (!IsDescendant(u,v))
        return false;
    int w = GetDescendantCost(v, u);
    return subtree_cost[u] < subtree_cost[u] + subtree_cost[v] - 2*w;
}

int CalcCostBottomUp(std::shared_ptr<graphs::WeightedTree> &tree,
                     std::vector<int> &delta,
                     std::vector<int> &cost,
                     int idx,
                     int p_idx) {
    cost[idx] = delta[idx];
    for (auto & ed : tree->vertices[idx].children)
        cost[idx] += CalcCostBottomUp(tree, delta, cost, ed.destIdx, idx);
    cost[idx];
    return cost[idx]; 
}
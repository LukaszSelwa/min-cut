#include "gmw_structure.hpp"

#include <algorithm>
#include <limits>

bool postord_range::contains(int x) { return begin <= x && x <= end; }

int calc_cost_bottomup(std::shared_ptr<graphs::weighted_tree>& tree, std::vector<int>& delta,
                       std::vector<int>& cost, int idx, int p_idx);

int gmw_structure::get_lower_endpoint(graphs::w_edge e) {
    return postorder[e.srcIdx].end < postorder[e.destIdx].end ? e.srcIdx : e.destIdx;
}

bool gmw_structure::is_descendant(int u, int v) {
    return postorder[u].begin <= postorder[v].end && postorder[v].end <= postorder[u].end;
}

bool gmw_structure::are_independent(int u, int v) {
    return !is_descendant(u, v) && !is_descendant(v, u);
}

int gmw_structure::get_independent_cost(int u, int v) {
    return rs->GetSumInRectangle(postorder[u].begin, postorder[u].end, postorder[v].begin,
                                 postorder[v].end);
}
int gmw_structure::get_descendant_cost(int u, int v) {
    return rs->GetSumInRectangle(postorder[v].begin, postorder[v].end, 1, postorder[u].begin - 1) +
           rs->GetSumInRectangle(postorder[v].begin, postorder[v].end, postorder[u].end + 1, n);
}

gmw_structure::gmw_structure(std::unique_ptr<RangeSearchStructure> rs) : rs(std::move(rs)) {}

void gmw_structure::initialize(std::shared_ptr<graphs::weighted_graph> graph,
                               std::shared_ptr<graphs::weighted_tree> tree) {
    graphs::lca_computer lca(tree);
    lca.initialize();
    n = tree->size;
    // Algorithm according to Karger: Minimum Cuts in Near-Linear Time
    // (sum weights of outgoing edges from v_i) - 2 * (sum of edges whose endpoints' lca is v_i)
    std::vector<int> delta(n, 0);
    for (auto& v : graph->vertices) {
        for (auto& ed : v.neighbors) {
            delta[v.get_idx()] += ed.weight;
            delta[lca.calc_lca(ed.srcIdx, ed.destIdx)] -= ed.weight;
        }
    }
    subtreeCost = std::vector<int>(n, 0);
    postorder = std::vector<postord_range>(n);
    calc_cost_bottomup(tree, delta, subtreeCost, tree->rootIdx, -1);
    subtreeCost[tree->rootIdx] = std::numeric_limits<int>::max();
    int nextPostorder = 1;

    tree->run_postorder([&](graphs::tree_vertice& v) {
        postorder[v.idx].begin = postorder[v.idx].end = nextPostorder++;
        for (auto& ed : v.children) {
            postorder[v.idx].begin = std::min(postorder[ed.destIdx].begin, postorder[v.idx].begin);
        }
    });

    for (const auto& v : graph->vertices) {
        for (const auto& ed : v.neighbors) {
            rs->AddPoint(postorder[ed.srcIdx].end, postorder[ed.destIdx].end, ed.weight);
        }
    }
}

int gmw_structure::get_cut_val(graphs::w_edge e1, graphs::w_edge e2) {
    // According to Gawrychowski, Mozes, Weimann: A Note on a Recent Algorithm for Minimum Cut
    int u = get_lower_endpoint(e1), v = get_lower_endpoint(e2);
    int w = 0;
    if (u == v) return subtreeCost[u];
    if (is_descendant(u, v))
        w = get_descendant_cost(u, v);
    else if (is_descendant(v, u))
        w = get_descendant_cost(v, u);
    else
        w = get_independent_cost(u, v);
    return subtreeCost[u] + subtreeCost[v] - 2 * w;
}

bool gmw_structure::is_crossinterested(graphs::w_edge e1, graphs::w_edge e2) {
    int u = get_lower_endpoint(e1), v = get_lower_endpoint(e2);
    if (is_descendant(u, v)) return false;
    int w = 0;
    if (is_descendant(v, u))
        w = rs->GetSumInRectangle(postorder[u].begin, postorder[u].end, postorder[v].begin,
                                  postorder[u].begin - 1) +
            rs->GetSumInRectangle(postorder[u].begin, postorder[u].end, postorder[u].end + 1,
                                  postorder[v].end);
    else
        w = get_independent_cost(u, v);
    return subtreeCost[u] < 2 * w;
}

bool gmw_structure::is_crossinterested(int idx, postord_range pr) {
    int w = 0;
    if (!pr.contains(postorder[idx].end))
        w = rs->GetSumInRectangle(postorder[idx].begin, postorder[idx].end, pr.begin, pr.end);
    else
        w = rs->GetSumInRectangle(postorder[idx].begin, postorder[idx].end, pr.begin,
                                  postorder[idx].begin - 1) +
            rs->GetSumInRectangle(postorder[idx].begin, postorder[idx].end, postorder[idx].end + 1,
                                  pr.end);
    return subtreeCost[idx] < 2 * w;
}

bool gmw_structure::is_downinterested(graphs::w_edge e1, graphs::w_edge e2) {
    int u = get_lower_endpoint(e1), v = get_lower_endpoint(e2);
    return is_descendant(v, u) ||
           (is_descendant(u, v) && subtreeCost[u] < 2 * get_descendant_cost(u, v));
}

bool gmw_structure::is_downinterested(int idx, postord_range pr) {
    int w = rs->GetSumInRectangle(1, postorder[idx].begin - 1, pr.begin, pr.end) +
            rs->GetSumInRectangle(postorder[idx].end + 1, n, pr.begin, pr.end);
    return subtreeCost[idx] < 2 * w;
}

int calc_cost_bottomup(std::shared_ptr<graphs::weighted_tree>& tree, std::vector<int>& delta,
                       std::vector<int>& cost, int idx, int p_idx) {
    cost[idx] = delta[idx];
    for (auto& ed : tree->vertices[idx].children)
        cost[idx] += calc_cost_bottomup(tree, delta, cost, ed.destIdx, idx);
    cost[idx];
    return cost[idx];
}
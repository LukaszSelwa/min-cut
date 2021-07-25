#include "hl_decomposition.hpp"

#include <iterator>

namespace graphs {

interested_path_pair::interested_path_pair(int idP, int idQ) : idP(idP), idQ(idQ) {}

void interested_path_pair::add_interested_edge(int pathId, w_edge& edge) {
    if (pathId == idP)
        edgesP.push_back(edge);
    else
        edgesQ.push_back(edge);
}

hl_decomposition::hl_decomposition(std::shared_ptr<weighted_tree> tree) : tree(tree) {}

struct hl_recurrence {
    int weight;
    int hlPathId;
};

hl_recurrence hl_decompose(int idx, std::vector<tree_vertice>& vertices, int& unusedId) {
    int weight = 1;
    hl_recurrence heaviest{-1, -1};
    hl_recurrence child;
    for (auto& e : vertices[idx].children) {
        child = hl_decompose(e.destIdx, vertices, unusedId);
        weight += child.weight;
        heaviest = child.weight > heaviest.weight ? child : heaviest;
    }

    if (2 * heaviest.weight >= weight)
        vertices[idx].hlPathId = heaviest.hlPathId;
    else
        vertices[idx].hlPathId = unusedId++;
    return hl_recurrence{.weight = weight, .hlPathId = vertices[idx].hlPathId};
}

void hl_decomposition::calc_hld_path_edges(int idx, int root, std::vector<tree_vertice>& vertices) {
    auto& v = vertices[idx];
    for (auto& e : v.children) calc_hld_path_edges(e.destIdx, root, vertices);

    if (v.idx != root) paths[v.hlPathId].edges.push_back(v.parentEdge);
}

void hl_decomposition::decompose() {
    int unusedPathId = 0;
    hl_decompose(tree->rootIdx, tree->vertices, unusedPathId);
    paths = std::vector<hl_path>(unusedPathId);
    for (int i = 0; i < unusedPathId; ++i) {
        paths[i].id = i;
        paths[i].interestedPaths.clear();
    }
    calc_hld_path_edges(tree->rootIdx, tree->rootIdx, tree->vertices);
}

void hl_decomposition::find_interested_paths(int pathId, int idx) {
    while (idx != tree->rootIdx) {
        auto& v = tree->vertices[idx];
        paths[pathId].interestedPaths[v.hlPathId] = -1;
        idx = v.parentEdge.destIdx;
    }
}

void hl_decomposition::find_interested_pairs_of_paths() {
    for (auto& v : tree->vertices) {
        if (v.idx != tree->rootIdx) {
            find_interested_paths(v.hlPathId, v.bottomCrossinterested);
            find_interested_paths(v.hlPathId, v.bottomDowninterested);
        }
    }
    interesting_pairs.clear();
    for (auto& p1 : paths) {
        for (auto& it1 : p1.interestedPaths) {
            if (it1.second != -1 || it1.first == p1.id) continue;
            hl_path& p2 = paths[it1.first];
            auto it2 = p2.interestedPaths.find(p1.id);
            if (it2 != p2.interestedPaths.end()) {
                it1.second = it2->second = interesting_pairs.size();
                interesting_pairs.emplace_back(p1.id, p2.id);
            }
        }
    }
}

void hl_decomposition::find_interested_path_edges(int pathId, w_edge edge, int idx) {
    int pairIdx;
    while (idx != tree->rootIdx) {
        auto& v = tree->vertices[idx];
        pairIdx = paths[pathId].interestedPaths[v.hlPathId];
        if (pairIdx != -1) {
            interesting_pairs[pairIdx].add_interested_edge(pathId, edge);
        }
        idx = v.parentEdge.destIdx;
    }
}

void hl_decomposition::find_interested_path_edges() {
    for (auto v : tree->vertices) {
        if (v.idx != tree->rootIdx) {
            find_interested_path_edges(v.hlPathId, v.parentEdge, v.bottomCrossinterested);
            find_interested_path_edges(v.hlPathId, v.parentEdge, v.bottomDowninterested);
        }
    }
}

void hl_decomposition::sort_paths_edges_root_wards(std::shared_ptr<gmw_structure> gmw) {
    auto& postorder = gmw->postorder;
    auto sortRootWards = [&](const w_edge& e1, const w_edge& e2) -> bool {
        return postorder[e1.srcIdx].end < postorder[e2.srcIdx].end;
    };
    for (auto& pair : interesting_pairs) {
        std::sort(pair.edgesP.begin(), pair.edgesP.end(), sortRootWards);
        pair.edgesP.erase(std::unique(pair.edgesP.begin(), pair.edgesP.end()), pair.edgesP.end());
        std::sort(pair.edgesQ.begin(), pair.edgesQ.end(), sortRootWards);
        pair.edgesQ.erase(std::unique(pair.edgesQ.begin(), pair.edgesQ.end()), pair.edgesQ.end());
    }
}

void hl_decomposition::transform_interesting_pairs(std::shared_ptr<gmw_structure> gmw) {
    std::vector<interested_path_pair> additional_pairs(0);
    int lastP, lastQ, firstQ;
    for (auto& pair : interesting_pairs) {
        lastP = pair.edgesP.back().srcIdx;
        lastQ = pair.edgesQ.back().srcIdx;

        // if both edge lists are independent its, ok
        if (gmw->are_independent(lastP, lastQ)) {
            std::reverse(pair.edgesQ.begin(), pair.edgesQ.end());
            continue;
        }

        if (gmw->is_descendant(lastP, lastQ)) {
            std::swap(pair.idP, pair.idQ);
            std::swap(pair.edgesP, pair.edgesQ);
            std::swap(lastP, lastQ);
        }
        firstQ = pair.edgesQ[0].srcIdx;
        if (gmw->is_descendant(firstQ, lastP)) continue;

        auto firstDesc = --pair.edgesQ.end();
        while (firstDesc != pair.edgesQ.begin() && gmw->is_descendant(firstDesc->srcIdx, lastP))
            --firstDesc;
        ++firstDesc;

        additional_pairs.emplace_back(pair.idP, pair.idQ);
        interested_path_pair& nPair = additional_pairs.back();
        nPair.edgesP = pair.edgesP;
        nPair.edgesQ = std::vector<w_edge>(pair.edgesQ.begin(), firstDesc);
        std::reverse(nPair.edgesQ.begin(), nPair.edgesQ.end());

        pair.edgesQ.erase(pair.edgesQ.begin(), firstDesc);
    }

    interesting_pairs.insert(interesting_pairs.end(),
                             std::make_move_iterator(additional_pairs.begin()),
                             std::make_move_iterator(additional_pairs.end()));
}

void hl_decomposition::initialize(std::shared_ptr<gmw_structure> gmw) {
    decompose();
    find_interested_pairs_of_paths();
    find_interested_path_edges();
    sort_paths_edges_root_wards(gmw);
    transform_interesting_pairs(gmw);
}

}  // namespace graphs

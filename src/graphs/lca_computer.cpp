#include "lca_computer.hpp"

namespace graphs {

lca_computer::lca_computer(std::shared_ptr<graphs::weighted_tree> tree): tree(tree) { }

void lca_computer::initialize() {
    reIndex = reIndexInv = firstVisit = std::vector<int> (tree->size, -1);
    std::vector<int> visitList(0);
    int unusedIdx = 0;

    in_order_traverse(tree->rootIdx, &unusedIdx, &visitList);
    minInOrder.Initialize(visitList.data(), visitList.data() + visitList.size());
}

int lca_computer::calc_lca(int aIdx, int bIdx) {
    if (firstVisit[aIdx] > firstVisit[bIdx])
        std::swap(aIdx, bIdx);
    int reLca = minInOrder.Min(firstVisit[aIdx], firstVisit[bIdx]);
    return reIndexInv[reLca];
}

void lca_computer::in_order_traverse(int idx, int* unusedIdx, std::vector<int>* visitList) {
    reIndex[idx] = (*unusedIdx)++;
    reIndexInv[reIndex[idx]] = idx;

    firstVisit[idx] = visitList->size();
    visitList->push_back(reIndex[idx]);
    for (auto edge : tree->vertices[idx].children) {
        in_order_traverse(edge.destIdx, unusedIdx, visitList);
            visitList->push_back(reIndex[idx]);
    }
}

}
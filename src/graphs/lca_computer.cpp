#include "lca_computer.hpp"

namespace graphs {

LCAComputer::LCAComputer(std::shared_ptr<graphs::WeightedTree> tree): tree(tree) { }

void LCAComputer::Initialize() {
    reIndex = reIndexInv = firstVisit = std::vector<int> (tree->size, -1);
    std::vector<int> visitList(0);
    int unusedIdx = 0;

    inOrderTraverse(tree->rootIdx, -1, &unusedIdx, &visitList);
    minInOrder.Initialize(visitList.data(), visitList.data() + visitList.size());
}

int LCAComputer::LCA(int aIdx, int bIdx) {
    if (firstVisit[aIdx] > firstVisit[bIdx])
        std::swap(aIdx, bIdx);
    int reLca = minInOrder.Min(firstVisit[aIdx], firstVisit[bIdx]);
    return reIndexInv[reLca];
}

void LCAComputer::inOrderTraverse(int idx, int parentIdx, int* unusedIdx, std::vector<int>* visitList) {
    reIndex[idx] = (*unusedIdx)++;
    reIndexInv[reIndex[idx]] = idx;

    firstVisit[idx] = visitList->size();
    visitList->push_back(reIndex[idx]);
    for (auto edge : tree->vertices[idx].GetNeighbors()) {
        if (edge.destIdx != parentIdx) {
            inOrderTraverse(edge.destIdx, idx, unusedIdx, visitList);
            visitList->push_back(reIndex[idx]);
        }
    }
}

}
#ifndef LCA_COMPUTER
#define LCA_COMPUTER
#include "weighted_tree.hpp"
#include "../range_search/range_min.hpp"
#include <memory>
#include <vector>

namespace graphs {

class LCAComputer {
    std::shared_ptr<graphs::WeightedTree> tree;
    RangeMin minInOrder;
    std::vector<int> reIndex;
    std::vector<int> reIndexInv;
    std::vector<int> firstVisit;

  public:
    LCAComputer(std::shared_ptr<graphs::WeightedTree> tree);
    void Initialize();
    int LCA(int aIdx, int bIdx);
    void inOrderTraverse(int idx, int *unusedIdx, std::vector<int>* visitList);
};

}
#endif /* LCA_COMPUTER */
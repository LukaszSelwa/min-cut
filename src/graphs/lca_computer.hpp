#ifndef LCA_COMPUTER
#define LCA_COMPUTER
#include "weighted_tree.hpp"
#include "../range_search/range_min.hpp"
#include <vector>

namespace graphs {

class LCAComputer {
    WeightedTree* tree;
    RangeMin minInOrder;
    std::vector<int> reIndex;
    std::vector<int> reIndexInv;
    std::vector<int> firstVisit;

  public:
    LCAComputer(WeightedTree* tree);
    void Initialize();
    int LCA(int aIdx, int bIdx);
    void inOrderTraverse(int idx, int parentIdx, int *unusedIdx, std::vector<int>* visitList);
};

}
#endif /* LCA_COMPUTER */
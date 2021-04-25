#ifndef LCA_COMPUTER
#define LCA_COMPUTER
#include "weighted_tree.hpp"
#include "../range_search/range_max.hpp"
#include <memory>

namespace graphs {

class LCAComputer {
    WeightedTree* tree;
    RangeMax minPreorder;

  public:
    LCAComputer(WeightedTree* tree);
    void Initialize();
    int LCA(int aIdx, int bIdx);
};

}
#endif /* LCA_COMPUTER */
#ifndef LCA_COMPUTER
#define LCA_COMPUTER
#include "weighted_tree.hpp"
#include "../range_search/range_min.hpp"
#include <memory>
#include <vector>

namespace graphs {

class lca_computer {
    std::shared_ptr<graphs::WeightedTree> tree;
    RangeMin minInOrder;
    std::vector<int> reIndex;
    std::vector<int> reIndexInv;
    std::vector<int> firstVisit;

  public:
    lca_computer(std::shared_ptr<graphs::WeightedTree> tree);
    void initialize();
    int calc_lca(int aIdx, int bIdx);
    void in_order_traverse(int idx, int *unusedIdx, std::vector<int>* visitList);
};

}
#endif /* LCA_COMPUTER */
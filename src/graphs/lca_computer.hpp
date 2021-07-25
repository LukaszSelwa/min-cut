#ifndef LCA_COMPUTER
#define LCA_COMPUTER
#include <memory>
#include <vector>

#include "../range_search/range_min.hpp"
#include "weighted_tree.hpp"

namespace graphs {

class lca_computer {
    std::shared_ptr<graphs::weighted_tree> tree;
    RangeMin minInOrder;
    std::vector<int> reIndex;
    std::vector<int> reIndexInv;
    std::vector<int> firstVisit;

   public:
    lca_computer(std::shared_ptr<graphs::weighted_tree> tree);
    void initialize();
    int calc_lca(int aIdx, int bIdx);
    void in_order_traverse(int idx, int* unusedIdx, std::vector<int>* visitList);
};

}  // namespace graphs
#endif /* LCA_COMPUTER */
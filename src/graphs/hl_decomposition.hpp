#ifndef HL_DECOMPOSITION_H
#define HL_DECOMPOSITION_H
#include "weighted_tree.hpp"
#include <memory>

namespace graphs {

struct hl_path {
    int id;
};

class hl_decomposition {
  private:
    std::shared_ptr<WeightedTree> tree;
  public:
    std::vector<hl_path> paths;
    hl_decomposition(std::shared_ptr<WeightedTree> tree);
    void decompose();
};

}


#endif /* HL_DECOMPOSITION */
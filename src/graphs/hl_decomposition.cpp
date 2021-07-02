#include "hl_decomposition.hpp"

namespace graphs {

hl_decomposition::hl_decomposition(std::shared_ptr<WeightedTree> tree): tree(tree) { }

struct hl_recurrence {
    int weight;
    int hlPathId;
};

hl_recurrence hl_decompose(int idx, std::vector<TreeVertice> & vertices, int & unusedId) {
    int weight = 1;
    hl_recurrence heaviest{-1,-1};
    hl_recurrence child;
    for (auto & e : vertices[idx].children) {
        child = hl_decompose(e.destIdx, vertices, unusedId);
        weight += child.weight;
        heaviest = child.weight > heaviest.weight ? child : heaviest;
    }

    if (2 * heaviest.weight >= weight)
        vertices[idx].hlPathId = heaviest.hlPathId;
    else 
        vertices[idx].hlPathId = unusedId++;
    return hl_recurrence{.weight=weight, .hlPathId=vertices[idx].hlPathId};
}

void hl_decomposition::decompose() {
    int unusedPathId = 0;
    hl_decompose(tree->rootIdx, tree->vertices, unusedPathId);
    paths = std::vector<hl_path>(unusedPathId);
    for (int i = 0; i < unusedPathId; ++i)
        paths[i].id = i;
}

}
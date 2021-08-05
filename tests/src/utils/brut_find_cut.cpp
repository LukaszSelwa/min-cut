#include "brut_find_cut.hpp"

#include "../../../src/graphs/gmw_structure.hpp"
#include "../../../src/range_search/segment_2d_point_tree.hpp"
namespace utils {

edge_pair brut_find_cut(std::shared_ptr<graphs::weighted_tree> tree,
                        std::shared_ptr<gmw_structure> gmw) {
    edge_pair result{.e1 = NIL_EDGE, .e2 = NIL_EDGE, .val = std::numeric_limits<int>::max()};
    for (auto& v1 : tree->vertices) {
        for (auto& v2 : tree->vertices) {
            if (v1.idx == tree->rootIdx || v2.idx == tree->rootIdx) continue;
            int val = gmw->get_cut_val(v1.parentEdge, v2.parentEdge);
            if (val < result.val)
                result = edge_pair{.e1 = v1.parentEdge, .e2 = v2.parentEdge, .val = val};
        }
    }
    return result;
}

void run_multiple_tests(int testCases, int maxN, int maxWeight,
                        std::function<void(int, int, std::mt19937)> testFunc) {
    std::random_device rd;
    std::mt19937 seed;
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--) testFunc(distN(seed), maxWeight, seed);
}

}  // namespace utils
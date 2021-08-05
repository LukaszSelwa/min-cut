#include "brut_find_cut_impl.hpp"

#include "../../../src/range_search/segment_2d_point_tree.hpp"
namespace utils {

template <class ALGO>
void test_find_cut(std::shared_ptr<graphs::weighted_graph> graph,
                   std::shared_ptr<graphs::weighted_tree> tree) {
    ALGO algo(graph, tree);
    algo.initialize();
    auto gmw =
        std::make_shared<gmw_structure>(std::make_unique<segment_2d_point_tree>(graph->size + 1));
    gmw->initialize(graph, tree);

    auto res = algo.find_cut();
    auto exp = utils::brut_find_cut(tree, gmw);
    ASSERT_EQ(res.val, exp.val) << "should find minimum VALUE for graph: " << *graph
                                << " and spanning tree" << *tree;
    if (res.val != std::numeric_limits<int>::max())
        ASSERT_EQ(res.val, gmw->get_cut_val(res.e1, res.e2))
            << "should also find minimum CUT for graph: " << *graph << " and spanning tree"
            << *tree;
}

template <class ALGO>
void test_find_cut_random_graph(int n, int maxWeight, std::mt19937 seed) {
    std::uniform_int_distribution<> dist(n - 1, n * (n - 1) / 2);
    auto sharedSeed = std::make_shared<std::mt19937>(seed);
    int m = dist(seed);
    auto graph = graphs::generate_random_graph(n, m, maxWeight, sharedSeed);
    std::shared_ptr<graphs::weighted_tree> tree(
        new graphs::weighted_tree(extractSingleRandomSpanningTree(*graph, sharedSeed)));

    utils::test_find_cut<ALGO>(graph, tree);
}

}  // namespace utils
#include <gtest/gtest.h>
#include <algorithm>
#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graphs/hl_decomposition.hpp"
#include "../../../src/range_search/interval2D_tree.hpp"
#include <iostream>

TEST(Graphs_HLDecomposition, Decompose_SmallTest_1) {
    auto e = examples::get_example(1);
    auto graph = e.graph;
    auto tree = e.spanningTree;

    graphs::hl_decomposition hld(tree);
    hld.decompose();
    std::vector<int> ctr(hld.paths.size(), 0);
    for (auto & v : tree->vertices) {
        if (v.idx != tree->rootIdx)
            ctr[v.hlPathId]++;
    }
    std::sort(ctr.begin(), ctr.end());
    std::vector<int> expCtr{1, 2, 4};
    EXPECT_EQ(ctr, expCtr);
}


TEST(Graphs_HLDecomposition, Initialize_SmallTest_1) {
    auto e = examples::get_example(1);
    auto graph = e.graph;
    auto tree = e.spanningTree;
    std::shared_ptr<gmw_structure> gmw(new gmw_structure(std::make_unique<Interval2DTree>(9, 9)));
    gmw->initialize(graph, tree);
    {
        graphs::binarized_tree bTree(tree, gmw);
        bTree.initialize();
        for (auto & v : tree->vertices) {
            if (v.idx != tree->rootIdx) {
                v.bottomCrossinterested = bTree.find_bottom_crossinterested(v.parentEdge);
                v.bottomDowninterested = bTree.find_bottom_downinterested(v.parentEdge);
            }
        }
    }

    graphs::hl_decomposition hld(tree);
    hld.initialize(gmw);
}
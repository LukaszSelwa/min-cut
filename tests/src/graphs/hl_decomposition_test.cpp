#include <gtest/gtest.h>
#include <algorithm>
#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graphs/hl_decomposition.hpp"

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

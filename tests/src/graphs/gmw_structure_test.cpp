#include <gtest/gtest.h>
#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/graphs/gmw_structure.hpp"
#include "../../../src/graphs/random_graph_generation.hpp"
#include "../../../src/range_search/interval2D_tree.hpp"
#include "../../../src/spanning_trees_extractors/random_spanning_trees_extractor.hpp"
#include <algorithm>
#include <memory>
#include <random>

class gmw_verifier {
    std::shared_ptr<graphs::weighted_graph> graph;
    std::shared_ptr<graphs::weighted_tree> tree;

  public:
    gmw_verifier(std::shared_ptr<graphs::weighted_graph> graph, std::shared_ptr<graphs::weighted_tree> tree): graph(graph), tree(tree) { }
    int get_cut_val(graphs::w_edge e1, graphs::w_edge e2) {
        std::vector<bool> cut(graph->size, false);

        std::function<void(int,bool)> calcCut = [&](int idx, bool isCut){
            cut[idx] = isCut;
            for (auto & e : tree->vertices[idx].children) {
                calcCut(e.destIdx, (e.is_equal(e1) || e.is_equal(e2)) != isCut);
            }
        };
        calcCut(tree->rootIdx, true);

        int cutVal = 0;
        for (auto & v : graph->vertices) {
            for (auto & e : v.neighbors)
                cutVal += cut[e.srcIdx] != cut[e.destIdx] ? e.weight : 0;
        }
        return cutVal / 2;
    }
};

void verifyCutVals(gmw_structure & gmwStr, std::shared_ptr<graphs::weighted_graph> graph, std::shared_ptr<graphs::weighted_tree> tree) {
    gmw_verifier gmwVer(graph, tree);
    std::vector<graphs::w_edge> edges(0);
    for (auto & v : tree->vertices) {
        for (auto & e : v.children)
            edges.push_back(e);
    }

    for (size_t i = 0; i < edges.size(); ++i) {
        for (int j = 0; j < i; ++j)
            ASSERT_EQ(gmwStr.get_cut_val(edges[i], edges[j]), gmwVer.get_cut_val(edges[i], edges[j])) 
                << "should calc cut value for edges: " << edges[i] << ", " << edges[j] << "\n" << *graph << "\n" << *tree;
    }
}

TEST(Graphs_GMWStructure, GMWExampleTest_1) {
    auto example = examples::get_example(1);
    auto graph = example.graph;
    auto tree = example.spanningTree;

    gmw_structure gmw(std::make_unique<Interval2DTree>(9, 9));
    gmw.initialize(graph, tree);

    std::vector<int> expCost{0, 5, 10, 9, 6, 12, 8, 5};
    std::vector<postord_range> expPost{{1,8}, {1,6}, {1,3}, {1,2}, {7,7}, {4,5}, {4,4}, {1,1}};
    EXPECT_EQ(gmw.subtreeCost, expCost);
    EXPECT_EQ(gmw.postorder, expPost);

    EXPECT_EQ(gmw.get_cut_val(graphs::w_edge(1, 5), graphs::w_edge(2, 3)), 11);
    EXPECT_EQ(gmw.get_cut_val(graphs::w_edge(0, 1), graphs::w_edge(2, 3)), 14);
    verifyCutVals(gmw, graph, tree);
}

TEST(Graphs_GMWStructure, GMWExampleTest_2) {
    auto example = examples::get_example(2);
    auto graph = example.graph;
    auto tree = example.spanningTree;

    gmw_structure gmw(std::make_unique<Interval2DTree>(11, 11));
    gmw.initialize(graph, tree);
    EXPECT_EQ(gmw.get_cut_val(graphs::w_edge(0, 8), graphs::w_edge(0, 9)), 16);
}


void testRandomGraph(int n, int maxWeight, std::shared_ptr<std::mt19937> seed) {
    std::uniform_int_distribution<> dist(n-1, n * (n-1) / 2);
    int m = dist(*seed);
    auto graph = graphs::generate_random_graph(n, m, maxWeight, seed);
    std::shared_ptr<graphs::weighted_tree> tree(new graphs::weighted_tree(extractSingleRandomSpanningTree(*graph, seed)));

    gmw_structure gmw(std::make_unique<Interval2DTree>(n+1, n+1));
    gmw.initialize(graph, tree);
    verifyCutVals(gmw, graph, tree);
}

TEST(Graphs_GMWStructure, GMWRandomTest) {
    int testCases = 50;
    int maxN = 50;
    int maxWeight = 10;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937(rd()));
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--)
        testRandomGraph(distN(*seed), maxWeight, seed);
}

TEST(Graphs_GMWStructure, GMWRandomLargeTest) {
    int testCases = 2;
    int maxN = 200;
    int maxWeight = 300;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937());
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--)
        testRandomGraph(distN(*seed), maxWeight, seed);
}
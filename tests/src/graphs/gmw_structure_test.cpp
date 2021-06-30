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
    std::shared_ptr<graphs::UndirectedWeightedGraph> graph;
    std::shared_ptr<graphs::WeightedTree> tree;

  public:
    gmw_verifier(std::shared_ptr<graphs::UndirectedWeightedGraph> graph, std::shared_ptr<graphs::WeightedTree> tree): graph(graph), tree(tree) { }
    int get_cut_val(graphs::WeightedEdge e1, graphs::WeightedEdge e2) {
        std::vector<bool> cut(graph->size, false);

        std::function<void(int,bool)> calcCut = [&](int idx, bool isCut){
            cut[idx] = isCut;
            for (auto & e : tree->vertices[idx].children) {
                calcCut(e.destIdx, (e.IsEqual(e1) || e.IsEqual(e2)) != isCut);
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

void verifyCutVals(gmw_structure & gmwStr, std::shared_ptr<graphs::UndirectedWeightedGraph> graph, std::shared_ptr<graphs::WeightedTree> tree) {
    gmw_verifier gmwVer(graph, tree);
    std::vector<graphs::WeightedEdge> edges(0);
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
    std::vector<int> expPost{8, 6, 3, 2, 7, 5, 4, 1};
    std::vector<int> expSPost{1, 1, 1, 1, 7, 4, 4, 1};
    EXPECT_EQ(gmw.get_subtree_cost(), expCost);
    EXPECT_EQ(gmw.get_postorder_visit(), expPost);
    EXPECT_EQ(gmw.get_subtree_postorder_visit(), expSPost);

    EXPECT_EQ(gmw.get_cut_val(graphs::WeightedEdge(1, 5), graphs::WeightedEdge(2, 3)), 11);
    EXPECT_EQ(gmw.get_cut_val(graphs::WeightedEdge(0, 1), graphs::WeightedEdge(2, 3)), 14);
    verifyCutVals(gmw, graph, tree);
}

TEST(Graphs_GMWStructure, GMWExampleTest_2) {
    auto example = examples::get_example(2);
    auto graph = example.graph;
    auto tree = example.spanningTree;

    gmw_structure gmw(std::make_unique<Interval2DTree>(11, 11));
    gmw.initialize(graph, tree);
    EXPECT_EQ(gmw.get_cut_val(graphs::WeightedEdge(0, 8), graphs::WeightedEdge(0, 9)), 16);
}


void testRandomGraph(int n, int maxWeight, std::shared_ptr<std::mt19937> seed) {
    std::uniform_int_distribution<> dist(n-1, n * (n-1) / 2);
    int m = dist(*seed);
    auto graph = graphs::generateRandomGraph(n, m, maxWeight, seed);
    std::shared_ptr<graphs::WeightedTree> tree(new graphs::WeightedTree(extractSingleRandomSpanningTree(*graph, seed)));

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
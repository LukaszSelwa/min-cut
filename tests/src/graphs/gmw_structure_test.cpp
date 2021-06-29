#include <gtest/gtest.h>
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

TEST(Graphs_GMWStructure, GMWExampleTest) {
    std::shared_ptr<graphs::UndirectedWeightedGraph> graph(new graphs::UndirectedWeightedGraph(8));
    graph->AddEdge(graphs::WeightedEdge(0, 1, 2));
    graph->AddEdge(graphs::WeightedEdge(0, 4, 3));
    graph->AddEdge(graphs::WeightedEdge(1, 2, 3));
    graph->AddEdge(graphs::WeightedEdge(1, 5, 2));
    graph->AddEdge(graphs::WeightedEdge(2, 3, 4));
    graph->AddEdge(graphs::WeightedEdge(2, 6, 2));
    graph->AddEdge(graphs::WeightedEdge(3, 6, 2));
    graph->AddEdge(graphs::WeightedEdge(3, 7, 2));
    graph->AddEdge(graphs::WeightedEdge(4, 5, 3));
    graph->AddEdge(graphs::WeightedEdge(5, 6, 1));
    graph->AddEdge(graphs::WeightedEdge(6, 7, 3));

    std::shared_ptr<graphs::WeightedTree> tree(new graphs::WeightedTree(8));
    tree->AddChildEdge(0, 1, 2);
    tree->AddChildEdge(0, 4, 3);
    tree->AddChildEdge(1, 2, 3);
    tree->AddChildEdge(1, 5, 2);
    tree->AddChildEdge(2, 3, 4);
    tree->AddChildEdge(3, 7, 2);
    tree->AddChildEdge(5, 6, 1);

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

TEST(Graphs_GMWStructure, GMWExampleTest_1) {
    std::shared_ptr<graphs::UndirectedWeightedGraph> graph(new graphs::UndirectedWeightedGraph(10));
    graph->AddEdge(graphs::WeightedEdge(0, 6, 9));
    graph->AddEdge(graphs::WeightedEdge(0, 8, 1));
    graph->AddEdge(graphs::WeightedEdge(0, 9, 6));
    graph->AddEdge(graphs::WeightedEdge(0, 2, 8));
    graph->AddEdge(graphs::WeightedEdge(1, 5, 1));
    graph->AddEdge(graphs::WeightedEdge(1, 4, 0));
    graph->AddEdge(graphs::WeightedEdge(2, 6, 0));
    graph->AddEdge(graphs::WeightedEdge(3, 6, 3));
    graph->AddEdge(graphs::WeightedEdge(3, 8, 0));
    graph->AddEdge(graphs::WeightedEdge(4, 9, 1));
    graph->AddEdge(graphs::WeightedEdge(4, 7, 0));
    graph->AddEdge(graphs::WeightedEdge(5, 8, 5));    
    graph->AddEdge(graphs::WeightedEdge(6, 8, 6));
    graph->AddEdge(graphs::WeightedEdge(7, 8, 1));
    graph->AddEdge(graphs::WeightedEdge(7, 9, 6));
    
    std::shared_ptr<graphs::WeightedTree> tree(new graphs::WeightedTree(10));
    tree->AddChildEdge(0, 9, 6);
    tree->AddChildEdge(0, 8, 1);
    tree->AddChildEdge(0, 6, 9);
    tree->AddChildEdge(9, 4, 1);
    tree->AddChildEdge(4, 1, 0);
    tree->AddChildEdge(6, 2, 0);
    tree->AddChildEdge(8, 5, 5);
    tree->AddChildEdge(8, 3, 0);
    tree->AddChildEdge(9, 7, 6);

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

TEST(Graphs_gmw_structure, GMWRandomTest) {
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
    std::shared_ptr<std::mt19937> seed(new std::mt19937(rd()));
    std::uniform_int_distribution<> distN(1, maxN);
    while (testCases--)
        testRandomGraph(distN(*seed), maxWeight, seed);
}
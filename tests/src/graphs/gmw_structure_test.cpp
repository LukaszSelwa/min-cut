#include <gtest/gtest.h>
#include "../../../src/graphs/gmw_structure.hpp"
#include "../../../src/graphs/random_graph_generation.hpp"
#include "../../../src/range_search/interval2D_tree.hpp"
#include "../../../src/spanning_trees_extractors/random_spanning_trees_extractor.hpp"
#include <algorithm>
#include <memory>
#include <random>

class GMWVerifier {
    std::shared_ptr<graphs::UndirectedWeightedGraph> graph;
    std::shared_ptr<graphs::WeightedTree> tree;

  public:
    GMWVerifier(std::shared_ptr<graphs::UndirectedWeightedGraph> graph, std::shared_ptr<graphs::WeightedTree> tree): graph(graph), tree(tree) { }
    int GetCutVal(graphs::WeightedEdge e1, graphs::WeightedEdge e2) {
        std::vector<bool> cut(graph->size, false);

        std::function<void(int,int,bool)> calc_cut = [&](int idx, int p_idx, bool is_cut){
            cut[idx] = is_cut;
            for (auto & e : tree->vertices[idx].GetNeighbors()) {
                if (p_idx == e.destIdx)
                    continue;
                calc_cut(e.destIdx, idx, (e.IsEqual(e1) || e.IsEqual(e2)) != is_cut);
            }
        };
        calc_cut(tree->rootIdx, -1, true);

        int cut_val = 0;
        for (auto & v : graph->vertices) {
            for (auto & e : v.GetNeighbors())
                cut_val += cut[e.srcIdx] != cut[e.destIdx] ? e.weight : 0;
        }
        return cut_val / 2;
    }
};

void verifyCutVals(GMWStructure & gmw_str, std::shared_ptr<graphs::UndirectedWeightedGraph> graph, std::shared_ptr<graphs::WeightedTree> tree) {
    GMWVerifier gmw_ver(graph, tree);
    std::vector<graphs::WeightedEdge> edges(0);
    for (auto & v : tree->vertices) {
        for (auto & e : v.GetNeighbors()) {
            if (e.srcIdx < e.destIdx)
                edges.push_back(e);
        }
    }

    for (size_t i = 0; i < edges.size(); ++i) {
        for (int j = 0; j < i; ++j)
            ASSERT_EQ(gmw_str.GetCutVal(edges[i], edges[j]), gmw_ver.GetCutVal(edges[i], edges[j])) 
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
    tree->AddEdge(0, 1, 2);
    tree->AddEdge(0, 4, 3);
    tree->AddEdge(1, 2, 3);
    tree->AddEdge(1, 5, 2);
    tree->AddEdge(2, 3, 4);
    tree->AddEdge(3, 7, 2);
    tree->AddEdge(5, 6, 1);

    GMWStructure gmw(std::make_unique<Interval2DTree>(9, 9));
    gmw.Initialize(graph, tree);

    std::vector<int> exp_cost{0, 5, 10, 9, 6, 12, 8, 5};
    std::vector<int> exp_post{8, 6, 3, 2, 7, 5, 4, 1};
    std::vector<int> exp_s_post{1, 1, 1, 1, 7, 4, 4, 1};
    EXPECT_EQ(gmw.GetSubtreeCost(), exp_cost);
    EXPECT_EQ(gmw.GetPostorderVisit(), exp_post);
    EXPECT_EQ(gmw.GetSubtreePostorderVisit(), exp_s_post);

    EXPECT_EQ(gmw.GetCutVal(graphs::WeightedEdge(1, 5), graphs::WeightedEdge(2, 3)), 11);
    EXPECT_EQ(gmw.GetCutVal(graphs::WeightedEdge(0, 1), graphs::WeightedEdge(2, 3)), 14);
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
    tree->AddEdge(0, 9, 6);
    tree->AddEdge(0, 8, 1);
    tree->AddEdge(0, 6, 9);
    tree->AddEdge(4, 9, 1);
    tree->AddEdge(1, 4, 0);
    tree->AddEdge(2, 6, 0);
    tree->AddEdge(5, 8, 5);
    tree->AddEdge(3, 8, 0);
    tree->AddEdge(7, 9, 6);

    GMWStructure gmw(std::make_unique<Interval2DTree>(11, 11));
    gmw.Initialize(graph, tree);
    EXPECT_EQ(gmw.GetCutVal(graphs::WeightedEdge(0, 8), graphs::WeightedEdge(0, 9)), 16);
}


void testRandomGraph(int n, int max_weight, std::shared_ptr<std::mt19937> seed) {
    std::uniform_int_distribution<> dist(n-1, std::max(n * (n-1) / 4, n));
    int m = dist(*seed);
    auto graph = graphs::generateRandomGraph(n, m, max_weight, seed);
    std::shared_ptr<graphs::WeightedTree> tree(new graphs::WeightedTree(extractSingleRandomSpanningTree(*graph, seed)));

    GMWStructure gmw(std::make_unique<Interval2DTree>(n+1, n+1));
    gmw.Initialize(graph, tree);
    verifyCutVals(gmw, graph, tree);
}

TEST(Graphs_GMWStructure, GMWRandomTest) {
    int test_cases = 50;
    int max_n = 50;
    int max_weight = 10;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937(rd()));
    std::uniform_int_distribution<> dist_n(1, max_n);
    while (test_cases--)
        testRandomGraph(dist_n(*seed), max_weight, seed);
}

TEST(Graphs_GMWStructure, GMWRandomLargeTest) {
    int test_cases = 2;
    int max_n = 200;
    int max_weight = 300;

    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937(rd()));
    std::uniform_int_distribution<> dist_n(1, max_n);
    while (test_cases--)
        testRandomGraph(dist_n(*seed), max_weight, seed);
}
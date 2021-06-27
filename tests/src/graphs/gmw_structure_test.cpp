#include <gtest/gtest.h>
#include "../../../src/graphs/gmw_structure.hpp"
#include <memory>
#include "../../../src/range_search/interval2D_tree.hpp"

TEST(Graphs_GMWStructure, GMWInitializeTest) {
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
}
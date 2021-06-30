#include "graph_examples.hpp"

namespace examples {
    using namespace graphs;

graph_example get_example(int nr) {
    graph_example e;

    switch (nr) {
    case 1:
        e.graph = std::shared_ptr<UndirectedWeightedGraph>(new UndirectedWeightedGraph(8));
        e.graph->AddEdge(graphs::WeightedEdge(0, 1, 2));
        e.graph->AddEdge(graphs::WeightedEdge(0, 4, 3));
        e.graph->AddEdge(graphs::WeightedEdge(1, 2, 3));
        e.graph->AddEdge(graphs::WeightedEdge(1, 5, 2));
        e.graph->AddEdge(graphs::WeightedEdge(2, 3, 4));
        e.graph->AddEdge(graphs::WeightedEdge(2, 6, 2));
        e.graph->AddEdge(graphs::WeightedEdge(3, 6, 2));
        e.graph->AddEdge(graphs::WeightedEdge(3, 7, 2));
        e.graph->AddEdge(graphs::WeightedEdge(4, 5, 3));
        e.graph->AddEdge(graphs::WeightedEdge(5, 6, 1));
        e.graph->AddEdge(graphs::WeightedEdge(6, 7, 3));

        e.spanningTree = std::shared_ptr<WeightedTree>(new WeightedTree(8));
        e.spanningTree->AddChildEdge(0, 1, 2);
        e.spanningTree->AddChildEdge(0, 4, 3);
        e.spanningTree->AddChildEdge(1, 2, 3);
        e.spanningTree->AddChildEdge(1, 5, 2);
        e.spanningTree->AddChildEdge(2, 3, 4);
        e.spanningTree->AddChildEdge(3, 7, 2);
        e.spanningTree->AddChildEdge(5, 6, 1);
        break;
    
    case 2:
        e.graph = std::shared_ptr<UndirectedWeightedGraph>(new UndirectedWeightedGraph(10));
        e.graph->AddEdge(graphs::WeightedEdge(0, 6, 9));
        e.graph->AddEdge(graphs::WeightedEdge(0, 8, 1));
        e.graph->AddEdge(graphs::WeightedEdge(0, 9, 6));
        e.graph->AddEdge(graphs::WeightedEdge(0, 2, 8));
        e.graph->AddEdge(graphs::WeightedEdge(1, 5, 1));
        e.graph->AddEdge(graphs::WeightedEdge(1, 4, 0));
        e.graph->AddEdge(graphs::WeightedEdge(2, 6, 0));
        e.graph->AddEdge(graphs::WeightedEdge(3, 6, 3));
        e.graph->AddEdge(graphs::WeightedEdge(3, 8, 0));
        e.graph->AddEdge(graphs::WeightedEdge(4, 9, 1));
        e.graph->AddEdge(graphs::WeightedEdge(4, 7, 0));
        e.graph->AddEdge(graphs::WeightedEdge(5, 8, 5));    
        e.graph->AddEdge(graphs::WeightedEdge(6, 8, 6));
        e.graph->AddEdge(graphs::WeightedEdge(7, 8, 1));
        e.graph->AddEdge(graphs::WeightedEdge(7, 9, 6));

        e.spanningTree = std::shared_ptr<WeightedTree>(new WeightedTree(10));
        e.spanningTree->AddChildEdge(0, 9, 6);
        e.spanningTree->AddChildEdge(0, 8, 1);
        e.spanningTree->AddChildEdge(0, 6, 9);
        e.spanningTree->AddChildEdge(9, 4, 1);
        e.spanningTree->AddChildEdge(4, 1, 0);
        e.spanningTree->AddChildEdge(6, 2, 0);
        e.spanningTree->AddChildEdge(8, 5, 5);
        e.spanningTree->AddChildEdge(8, 3, 0);
        e.spanningTree->AddChildEdge(9, 7, 6);
        break;
    
    default:
        throw "Unsupported graph example number";
    }

    return e;
}

}
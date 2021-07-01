#include "graph_examples.hpp"

namespace examples {
    using namespace graphs;

graph_example get_example(int nr) {
    graph_example e;

    switch (nr) {
    case 1:
        e.graph = std::shared_ptr<weighted_graph>(new weighted_graph(8));
        e.graph->add_edge(graphs::w_edge(0, 1, 2));
        e.graph->add_edge(graphs::w_edge(0, 4, 3));
        e.graph->add_edge(graphs::w_edge(1, 2, 3));
        e.graph->add_edge(graphs::w_edge(1, 5, 2));
        e.graph->add_edge(graphs::w_edge(2, 3, 4));
        e.graph->add_edge(graphs::w_edge(2, 6, 2));
        e.graph->add_edge(graphs::w_edge(3, 6, 2));
        e.graph->add_edge(graphs::w_edge(3, 7, 2));
        e.graph->add_edge(graphs::w_edge(4, 5, 3));
        e.graph->add_edge(graphs::w_edge(5, 6, 1));
        e.graph->add_edge(graphs::w_edge(6, 7, 3));

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
        e.graph = std::shared_ptr<weighted_graph>(new weighted_graph(10));
        e.graph->add_edge(graphs::w_edge(0, 6, 9));
        e.graph->add_edge(graphs::w_edge(0, 8, 1));
        e.graph->add_edge(graphs::w_edge(0, 9, 6));
        e.graph->add_edge(graphs::w_edge(0, 2, 8));
        e.graph->add_edge(graphs::w_edge(1, 5, 1));
        e.graph->add_edge(graphs::w_edge(1, 4, 0));
        e.graph->add_edge(graphs::w_edge(2, 6, 0));
        e.graph->add_edge(graphs::w_edge(3, 6, 3));
        e.graph->add_edge(graphs::w_edge(3, 8, 0));
        e.graph->add_edge(graphs::w_edge(4, 9, 1));
        e.graph->add_edge(graphs::w_edge(4, 7, 0));
        e.graph->add_edge(graphs::w_edge(5, 8, 5));    
        e.graph->add_edge(graphs::w_edge(6, 8, 6));
        e.graph->add_edge(graphs::w_edge(7, 8, 1));
        e.graph->add_edge(graphs::w_edge(7, 9, 6));

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
    
    case 3: 
        e.graph = std::shared_ptr<weighted_graph>(new weighted_graph(7));
        e.graph->add_edge(graphs::w_edge(0, 4, 9));
        e.graph->add_edge(graphs::w_edge(0, 1, 10));
        e.graph->add_edge(graphs::w_edge(1, 6, 4));
        e.graph->add_edge(graphs::w_edge(1, 2, 5));
        e.graph->add_edge(graphs::w_edge(2, 5, 9));
        e.graph->add_edge(graphs::w_edge(2, 6, 9));
        e.graph->add_edge(graphs::w_edge(3, 4, 1));
        e.graph->add_edge(graphs::w_edge(3, 6, 3));
        e.graph->add_edge(graphs::w_edge(4, 5, 10));
        e.graph->add_edge(graphs::w_edge(4, 6, 10));
        e.graph->add_edge(graphs::w_edge(5, 6, 2));

        e.spanningTree = std::shared_ptr<WeightedTree>(new WeightedTree(10));
        e.spanningTree->AddChildEdge(0, 4, 9);
        e.spanningTree->AddChildEdge(4, 5, 10);
        e.spanningTree->AddChildEdge(4, 3, 1);
        e.spanningTree->AddChildEdge(5, 2, 9);
        e.spanningTree->AddChildEdge(5, 6, 2);
        e.spanningTree->AddChildEdge(2, 1, 5);
        break;
    default:
        throw "Unsupported graph example number";
    }

    return e;
}

}
#include "graph_examples.hpp"

namespace examples {
using namespace graphs;

input_graph get_example(int nr) {
    input_graph e;

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

            e.spanningTree = std::shared_ptr<weighted_tree>(new weighted_tree(8));
            e.spanningTree->add_child_edge(0, 1, 2);
            e.spanningTree->add_child_edge(0, 4, 3);
            e.spanningTree->add_child_edge(1, 2, 3);
            e.spanningTree->add_child_edge(1, 5, 2);
            e.spanningTree->add_child_edge(2, 3, 4);
            e.spanningTree->add_child_edge(3, 7, 2);
            e.spanningTree->add_child_edge(5, 6, 1);

            e.expectedMinCut = 4;
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

            e.spanningTree = std::shared_ptr<weighted_tree>(new weighted_tree(10));
            e.spanningTree->add_child_edge(0, 9, 6);
            e.spanningTree->add_child_edge(0, 8, 1);
            e.spanningTree->add_child_edge(0, 6, 9);
            e.spanningTree->add_child_edge(9, 4, 1);
            e.spanningTree->add_child_edge(4, 1, 0);
            e.spanningTree->add_child_edge(6, 2, 0);
            e.spanningTree->add_child_edge(8, 5, 5);
            e.spanningTree->add_child_edge(8, 3, 0);
            e.spanningTree->add_child_edge(9, 7, 6);

            e.expectedMinCut = 1;
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

            e.spanningTree = std::shared_ptr<weighted_tree>(new weighted_tree(7));
            e.spanningTree->add_child_edge(0, 4, 9);
            e.spanningTree->add_child_edge(4, 5, 10);
            e.spanningTree->add_child_edge(4, 3, 1);
            e.spanningTree->add_child_edge(5, 2, 9);
            e.spanningTree->add_child_edge(5, 6, 2);
            e.spanningTree->add_child_edge(2, 1, 5);
            break;

        case 4:
            e.graph = std::make_shared<weighted_graph>(7);
            e.graph->add_edge(graphs::w_edge(0, 6, 25));
            e.graph->add_edge(graphs::w_edge(0, 1, 16));
            e.graph->add_edge(graphs::w_edge(0, 3, 20));
            e.graph->add_edge(graphs::w_edge(0, 4, 39));
            e.graph->add_edge(graphs::w_edge(0, 5, 15));
            e.graph->add_edge(graphs::w_edge(1, 4, 35));
            e.graph->add_edge(graphs::w_edge(1, 2, 35));
            e.graph->add_edge(graphs::w_edge(2, 6, 39));
            e.graph->add_edge(graphs::w_edge(2, 5, 3));
            e.graph->add_edge(graphs::w_edge(2, 3, 9));
            e.graph->add_edge(graphs::w_edge(2, 4, 1));
            e.graph->add_edge(graphs::w_edge(4, 5, 10));
            e.graph->add_edge(graphs::w_edge(4, 6, 38));

            e.spanningTree = std::make_shared<weighted_tree>(7);
            e.spanningTree->add_child_edge(0, 3, 20);
            e.spanningTree->add_child_edge(0, 5, 15);
            e.spanningTree->add_child_edge(5, 4, 10);
            e.spanningTree->add_child_edge(4, 1, 35);
            e.spanningTree->add_child_edge(1, 2, 35);
            e.spanningTree->add_child_edge(2, 6, 39);

            e.expectedMinCut = 28;
            break;

        case 5:
            e.graph = std::make_shared<weighted_graph>(6);
            e.graph->add_edge(graphs::w_edge(0, 1, 32));
            e.graph->add_edge(graphs::w_edge(0, 2, 29));
            e.graph->add_edge(graphs::w_edge(0, 3, 2));
            e.graph->add_edge(graphs::w_edge(0, 4, 40));
            e.graph->add_edge(graphs::w_edge(1, 5, 4));
            e.graph->add_edge(graphs::w_edge(2, 5, 2));
            e.graph->add_edge(graphs::w_edge(3, 5, 15));
            e.graph->add_edge(graphs::w_edge(4, 5, 23));

            e.spanningTree = std::make_shared<weighted_tree>(6);
            e.spanningTree->add_child_edge(0, 3, 2);
            e.spanningTree->add_child_edge(3, 5, 15);
            e.spanningTree->add_child_edge(5, 2, 2);
            e.spanningTree->add_child_edge(5, 1, 4);
            e.spanningTree->add_child_edge(5, 4, 23);

            e.expectedMinCut = 17;
            break;
        default:
            throw "Unsupported graph example number";
    }

    return e;
}

}  // namespace examples
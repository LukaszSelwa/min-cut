#ifndef NAIVE_ALGO__FLOW_GRAPH_H
#define NAIVE_ALGO__FLOW_GRAPH_H
#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

namespace naive {

struct fg_edge {
    int dest;
    int capacity;
    int flow;
    fg_edge* reverse;

    fg_edge();
    fg_edge(int destination, int capacity);

    bool is_saturated() { return flow >= capacity; }
};

struct fg_node {
    std::deque<fg_edge> neigh;
    fg_node();
};

struct flow_graph {
    int source;
    int sink;
    std::vector<fg_node> V;

    explicit flow_graph(size_t size);
    void add_edge(int from, int to, int capacity);
    bool found_augmenting_path();
    int calc_max_flow();
    void clear_flow();
    void set_sink(int sink);
    void set_source(int source);
    std::vector<bool> get_min_cut();
};

}  // namespace naive

#endif /* NAIVE_ALGO__FLOW_GRAPH_H */
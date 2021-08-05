#ifndef MAIN_ALGO_COMMON_H
#define MAIN_ALGO_COMMON_H

#include "../graphs/undirected_weighted_graph.hpp"

struct edge_pair {
    graphs::w_edge e1, e2;
    int val;
    friend bool operator<(const edge_pair& p1, const edge_pair& p2);
};

const graphs::w_edge NIL_EDGE(-1, -1);

#endif /* MAIN_ALGO_COMMON_H */
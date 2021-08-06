#include "flow_graph.hpp"

namespace naive {
fg_edge::fg_edge() : dest(0), capacity(0), flow(0), reverse(nullptr) {}

fg_edge::fg_edge(int destination, int capacity)
    : dest(destination), capacity(capacity), flow(0), reverse(nullptr) {}

fg_node::fg_node() : neigh(std::deque<fg_edge>(0)) {}

flow_graph::flow_graph(size_t size)
    : source(0), sink((int)size - 1), V(std::vector<fg_node>(size)) {}

void flow_graph::add_edge(int from, int to, int capacity) {
    V[from].neigh.emplace_back(fg_edge(to, capacity));
    V[to].neigh.emplace_back(fg_edge(from, capacity));

    V[from].neigh.back().reverse = &V[to].neigh.back();
    V[to].neigh.back().reverse = &V[from].neigh.back();
}

bool flow_graph::found_augmenting_path() {
    int ver;
    std::vector<fg_edge*> prev(V.size(), nullptr);
    std::queue<int> Q;

    /* standard BFS */
    Q.push(source);
    fg_edge startEdge(0, 1);
    prev[source] = &startEdge;
    while (!Q.empty()) {
        ver = Q.front();
        Q.pop();
        for (fg_edge& ed : V[ver].neigh) {
            if (!ed.is_saturated() && prev[ed.dest] == nullptr) {
                prev[ed.dest] = &ed;
                Q.push(ed.dest);
            }
        }
    }

    if (prev[sink] == nullptr) /* No augmenting path exists. */
        return false;

    /* find minimal flow in the augmenting path */
    int minFlow = std::numeric_limits<int>::max();
    fg_edge* edgPtr = prev[sink];
    while (edgPtr != &startEdge) {
        minFlow = std::min(minFlow, edgPtr->capacity - edgPtr->flow);
        edgPtr = prev[edgPtr->reverse->dest];
    }

    /* Improve the flow. */
    edgPtr = prev[sink];
    while (edgPtr != &startEdge) {
        edgPtr->flow += minFlow;
        edgPtr->reverse->flow += -minFlow;
        edgPtr = prev[edgPtr->reverse->dest];
    }

    return true;
}

int flow_graph::calc_max_flow() {
    int result = 0;
    while (found_augmenting_path()) {
    }
    for (fg_edge& ed : V[source].neigh) result += ed.flow;
    return result;
}

void flow_graph::clear_flow() {
    for (auto& v : V) {
        for (auto& e : v.neigh) e.flow = 0;
    }
}

void flow_graph::set_sink(int sink) { this->sink = sink; }

void flow_graph::set_source(int source) { this->source = source; }

std::vector<bool> flow_graph::get_min_cut() {
    std::vector<bool> visited(V.size(), false);
    std::queue<int> visiting;
    int vIdx;

    visiting.push(source);
    visited[source] = true;
    while (!visiting.empty()) {
        vIdx = visiting.front();
        visiting.pop();
        for (auto& e : V[vIdx].neigh) {
            if (!e.is_saturated() && !visited[e.dest]) {
                visiting.push(e.dest);
                visited[e.dest] = true;
            }
        }
    }
    return visited;
}

}  // namespace naive
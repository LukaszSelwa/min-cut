#ifndef VERTICES_H
#define VERTICES_H
#include <iostream>
#include <vector>

namespace graphs {

class w_edge {
  public:
    int srcIdx;
    int destIdx;
    int weight;

    w_edge(int srcIdx, int destIdx, int weight): srcIdx(srcIdx), destIdx(destIdx), weight(weight) { }
    w_edge(int srcIdx, int destIdx): srcIdx(srcIdx), destIdx(destIdx), weight(1) { }
    w_edge(): w_edge(0, 0, 0) { }
    bool is_equal(const w_edge & e);
    friend std::ostream & operator<< (std::ostream &os, const w_edge & e);
};

class vertice {
    int myIdx;

  public:
    std::vector<w_edge> neighbors;
    
    vertice(): myIdx(0), neighbors(std::vector<w_edge>(0)) { }
    int get_idx() const;
    void set_idx(int idx);
    void add_neighbour(int idx, int weight);
};

}

#endif /* VERTICES_H */
#ifndef HL_DECOMPOSITION_H
#define HL_DECOMPOSITION_H
#include "weighted_tree.hpp"
#include "binarized_tree.hpp"
#include <memory>
#include <unordered_map>

namespace graphs {

struct hl_path {
    int id;
    /* If interestedPaths map contains key k and value v than:
     * - this path is cross or down interested in path with id k
     * - if v != -1 than path k is also interested in this path 
     *   and pair {id, k} has index v.
     */
    std::unordered_map<int, int> interestedPaths;
};

struct interested_path_pair {
    int idP, idQ;
    std::vector<w_edge> edgesP; // Edges of path.idP which are interested in path idQ
    std::vector<w_edge> edgesQ; // Edges of path.idQ which are interested in path idP
    interested_path_pair() { }
    interested_path_pair(int idP, int idQ);
    void add_interested_edge(int pathId, w_edge & edge);
};

class hl_decomposition {
  private:
    std::shared_ptr<weighted_tree> tree;
    void find_interested_paths(int pathId, int idx);
    void find_interested_path_edges(int pathId, w_edge edge, int idx);
  public:
    std::vector<hl_path> paths;
    std::vector<interested_path_pair> interesting_pairs;
    hl_decomposition(std::shared_ptr<weighted_tree> tree);
    void decompose();
    void find_interested_pairs_of_paths();
    void find_interested_path_edges();
    void sort_paths_edges_root_wards(std::shared_ptr<gmw_structure> gmw);
    void transform_interesting_pairs(std::shared_ptr<gmw_structure> gmw);
    void initialize(std::shared_ptr<gmw_structure> gmw);
};

}


#endif /* HL_DECOMPOSITION */
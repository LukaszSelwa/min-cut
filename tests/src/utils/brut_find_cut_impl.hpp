#ifndef BRUT_FIND_CUT_IMPL_H
#define BRUT_FIND_CUT_IMPL_H

#include <gtest/gtest.h>

#include <functional>
#include <memory>
#include <random>

#include "../../../src/graph_generation/random_graph_generation.hpp"
#include "../../../src/graphs/gmw_structure.hpp"
#include "../../../src/graphs/undirected_weighted_graph.hpp"
#include "../../../src/graphs/weighted_tree.hpp"
#include "../../../src/main_algo/common.hpp"
#include "../../../src/spanning_trees_extractors/random_spanning_trees_extractor.hpp"

namespace utils {

edge_pair brut_find_cut(std::shared_ptr<graphs::weighted_tree> tree,
                        std::shared_ptr<gmw_structure> gmw);

template <class ALGO>
void test_find_cut(std::shared_ptr<graphs::weighted_graph> graph,
                   std::shared_ptr<graphs::weighted_tree> tree);

template <class ALGO>
void test_find_cut_random_graph(int n, int maxWeight, std::mt19937 seed);

void run_multiple_tests(int testCases, int maxN, int maxWeight,
                        std::function<void(int, int, std::mt19937)> testFunc);

}  // namespace utils

#endif /* BRUT_FIND_CUT_IMPL_H */
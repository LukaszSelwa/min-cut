#ifndef RANDOM__WEIGHTED_QUEUE_TEMP_H
#define RANDOM__WEIGHTED_QUEUE_TEMP_H
#include <algorithm>
#include <memory>
#include <random>
#include <vector>

#include "suffix_tree.hpp"

template <typename T>
class random_weighted_queue {
    std::mt19937 seed;
    std::vector<T> arr;
    std::vector<int> weights;
    int sum;
    size_t size;

    suffix_tree sTree;

   public:
    random_weighted_queue(std::mt19937 seed);
    void initialize(std::vector<T> arr, std::vector<int> weights);
    T pop();
    bool empty();
};

#endif /* RANDOM__WEIGHTED_QUEUE_TEMP_H */
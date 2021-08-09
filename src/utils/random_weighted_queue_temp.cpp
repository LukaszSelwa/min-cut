#include "random_weighted_queue_temp.hpp"

#include <cmath>

template <typename T>
random_weighted_queue<T>::random_weighted_queue(std::shared_ptr<std::mt19937> seed)
    : seed(seed), sTree(0) {}

template <typename T>
void random_weighted_queue<T>::initialize(std::vector<T> arr, std::vector<int> weights) {
    this->arr = arr;
    this->weights = weights;
    sum = 0;
    size = weights.size();
    sTree = suffix_tree(size);

    for (int i = 0; i < size; ++i) {
        sum += weights[i];
        sTree.add_to_suffix(i, weights[i]);
    }
}

template <typename T>
T random_weighted_queue<T>::pop() {
    std::uniform_real_distribution<double> dist(0, sum);
    int val = std::lround(dist(*seed));
    int idx = sTree.first_geq_idx(val);

    sTree.add_to_suffix(idx, -weights[idx]);
    sum -= weights[idx];
    weights[idx] = 0;
    size--;

    return arr[idx];
}

template <typename T>
bool random_weighted_queue<T>::empty() {
    return size == 0;
}
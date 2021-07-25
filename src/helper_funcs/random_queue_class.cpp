#include "random_queue_class.hpp"

template <typename T>
RandomQueue<T>::RandomQueue(std::shared_ptr<std::mt19937> seed)
    : seed(seed), arr(std::vector<T>(0)) {}

template <typename T>
void RandomQueue<T>::push(T val) {
    arr.push_back(val);
}

template <typename T>
T RandomQueue<T>::pop() {
    std::uniform_int_distribution<> dist(0, arr.size() - 1);
    size_t idx = dist(*seed);
    T val = arr[idx];
    arr[idx] = arr.back();
    arr.pop_back();
    return val;
}

template <typename T>
bool RandomQueue<T>::empty() {
    return arr.empty();
}
#ifndef RANDOM_QUEUE_CLASS
#define RANDOM_QUEUE_CLASS
#include <algorithm>
#include <memory>
#include <random>
#include <vector>

template<typename T>
class RandomQueue {
    std::shared_ptr<std::mt19937> seed;
    std::vector<T> arr;
  public:
    RandomQueue(std::shared_ptr<std::mt19937> seed);
    void push(T val);
    T pop();
    bool empty();
};

#endif /* RANDOM_QUEUE_CLASS */
#include "../../../src/utils/random_weighted_queue.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <random>
#include <vector>

TEST(Utils_RandomWeightedQueue, EmptyQueueTest) {
    auto seed = std::make_shared<std::mt19937>();
    random_weighted_queue<int> rq(seed);
    rq.initialize(std::vector<int>{}, std::vector<int>{});
    EXPECT_TRUE(rq.empty()) << "Queue should be empty";
}

TEST(Utils_RandomWeightedQueue, SingleElement_Test) {
    auto seed = std::make_shared<std::mt19937>();
    random_weighted_queue<int> rq(seed);
    rq.initialize(std::vector<int>{42}, std::vector<int>{2});
    ASSERT_FALSE(rq.empty()) << "Queue should not be empty";
    ASSERT_EQ(rq.pop(), 42) << "Should get element";
    ASSERT_TRUE(rq.empty()) << "Queue should be empty";
}

TEST(Utils_RandomWeightedQueue, MultipleElements_Test) {
    auto seed = std::make_shared<std::mt19937>();
    random_weighted_queue<std::string> rq(seed);

    std::vector<std::string> in{"abc", "bca", "cab"};
    std::vector<int> weights{100, 10000, 1};
    std::vector<std::string> out(0);

    rq.initialize(in, weights);
    while (!rq.empty()) out.push_back(rq.pop());
    std::vector<std::string> expOut{"bca", "abc", "cab"};
    EXPECT_EQ(out, expOut) << "out should be a permutation of in";
}

TEST(Utils_RandomWeightedQueue, ManyMultipleElements_Test) {
    auto seed = std::make_shared<std::mt19937>();
    random_weighted_queue<int> rq(seed);

    std::vector<int> in(100);
    std::vector<int> weights(100);
    for (int i = 0; i < 100; ++i) {
        in[i] = i + 1;
        weights[i] = i + 1;
    }
    std::vector<int> out(0);

    rq.initialize(in, weights);
    while (!rq.empty()) out.push_back(rq.pop());
    std::sort(out.begin(), out.end());
    EXPECT_EQ(in, out) << "out should be a permutation of in";
}
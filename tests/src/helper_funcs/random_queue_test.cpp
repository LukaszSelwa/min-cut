#include "../../../src/helper_funcs/random_queue.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <random>
#include <vector>

TEST(HelperFuncs_RandomQueue, EmptyQueueTest) {
    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937(rd()));
    RandomQueue<int> rq(seed);
    ASSERT_TRUE(rq.empty()) << "Queue should be empty";
}

TEST(HelperFuncs_RandomQueue, SingleElement_Test) {
    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937(rd()));
    RandomQueue<int> rq(seed);
    rq.push(42);
    ASSERT_FALSE(rq.empty()) << "Queue should not be empty";
    ASSERT_EQ(rq.pop(), 42) << "Should get element";
    ASSERT_TRUE(rq.empty()) << "Queue should be empty";
}

TEST(HelperFuncs_RandomQueue, MultipleElements_Test) {
    std::random_device rd;
    std::shared_ptr<std::mt19937> seed(new std::mt19937(rd()));
    RandomQueue<std::string> rq(seed);

    std::vector<std::string> in{"abc", "bca", "cab"};
    std::vector<std::string> out(0);
    for (auto str : in) rq.push(str);
    while (!rq.empty()) out.push_back(rq.pop());
    std::sort(out.begin(), out.end());
    EXPECT_EQ(in, out) << "out should be a permutation of in";
}
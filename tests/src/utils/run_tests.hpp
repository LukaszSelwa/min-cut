#ifndef TEST_UTILS__RUN_RESTS_H
#define TEST_UTILS__RUN_RESTS_H

#include <functional>

namespace utils {

void run_multiple_tests(int testNr, std::function<bool()> testFunc);

}

#endif /* TEST_UTILS__RUN_RESTS_H */
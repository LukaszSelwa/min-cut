#include "run_tests.hpp"

#include <iostream>

namespace utils {

void run_multiple_tests(int testNr, std::function<bool()> testFunc) {
    for (int itr = 0; itr < testNr; ++itr) {
        std::cout << "\033[32m[          ]\033[33m Running test " << itr << "/" << testNr
                  << "\033[0m" << std::flush;
        if (!testFunc()) break;
        std::cout << "\r";
    }
}

}
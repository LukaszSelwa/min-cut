#include "helper_functions.hpp"

size_t ceilingLog(size_t x) {
    size_t log = 0;
    x = x > 0 ? x - 1 : 0;
    while (x > 0) {
        log++;
        x = x >> 1;
    }
    return log;
}

int parentInterval(int tIdx) { return tIdx / 2; }

int leftChildInterval(int tIdx) { return 2 * tIdx; }

int rightChildInterval(int tIdx) { return 2 * tIdx + 1; }

bool isLeftChild(int tIdx) { return (tIdx & 1) == 0; }

bool isRightChild(int tIdx) { return (tIdx & 1) == 1; }
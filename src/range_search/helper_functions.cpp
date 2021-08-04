#include "helper_functions.hpp"

size_t log_ceil(size_t x) {
    size_t log = 0;
    x = x > 0 ? x - 1 : 0;
    while (x > 0) {
        log++;
        x = x >> 1;
    }
    return log;
}

int parent_interval(int tIdx) { return tIdx / 2; }

int left_child_interval(int tIdx) { return 2 * tIdx; }

int right_child_interval(int tIdx) { return 2 * tIdx + 1; }

bool is_left_child(int tIdx) { return (tIdx & 1) == 0; }

bool is_right_child(int tIdx) { return (tIdx & 1) == 1; }
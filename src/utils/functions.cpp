#include "functions.hpp"

size_t log_ceil(size_t x) {
    size_t log = 0;
    x = x > 0 ? x - 1 : 0;
    while (x > 0) {
        log++;
        x = x >> 1;
    }
    return log;
}
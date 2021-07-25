#include "partial_monge_min.hpp"

#include <algorithm>

#include "smawk.hpp"

int recursive_partial_monge_min(const size_t rowBegin, const size_t colBegin, const size_t size,
                                std::function<int(size_t, size_t)> lookup);

int monge_sub_sqr_min(const size_t rowBegin, const size_t colBegin, const size_t size,
                      std::function<int(size_t, size_t)> lookup);

int partial_monge_min(const size_t size, std::function<int(size_t, size_t)> lookup) {
    return recursive_partial_monge_min(0, 0, size, lookup);
}

int recursive_partial_monge_min(const size_t rowBegin, const size_t colBegin, const size_t size,
                                std::function<int(size_t, size_t)> lookup) {
    size_t prefSize = size / 2;
    size_t sqrtSize = size - prefSize;

    int result = monge_sub_sqr_min(rowBegin + prefSize, colBegin, sqrtSize, lookup);

    if (prefSize > 0) {
        result =
            std::min(result, recursive_partial_monge_min(rowBegin, colBegin, prefSize, lookup));
        result = std::min(result, recursive_partial_monge_min(
                                      rowBegin + sqrtSize, colBegin + sqrtSize, prefSize, lookup));
    }

    return result;
}

int monge_sub_sqr_min(const size_t rowBegin, const size_t colBegin, const size_t size,
                      std::function<int(size_t, size_t)> lookup) {
    return smawk_min(size, size,
                     [&](size_t i, size_t j) -> int { return lookup(rowBegin + i, colBegin + j); });
}
#include "partial_monge_min.hpp"

#include <algorithm>

min_coords recursive_partial_monge_min(const size_t rowBegin, const size_t colBegin,
                                       const size_t size,
                                       std::function<int(size_t, size_t)> lookup);

min_coords monge_sub_sqr_min(const size_t rowBegin, const size_t colBegin, const size_t size,
                             std::function<int(size_t, size_t)> lookup);

min_coords partial_monge_min(const size_t size, std::function<int(size_t, size_t)> lookup) {
    return recursive_partial_monge_min(0, 0, size, lookup);
}

min_coords recursive_partial_monge_min(const size_t rowBegin, const size_t colBegin,
                                       const size_t size,
                                       std::function<int(size_t, size_t)> lookup) {
    size_t prefSize = size / 2;
    size_t sqrtSize = size - prefSize;

    min_coords result = monge_sub_sqr_min(rowBegin, colBegin, sqrtSize, lookup);

    if (prefSize > 0) {
        min_coords result_rec;
        result_rec = recursive_partial_monge_min(rowBegin + sqrtSize, colBegin, prefSize, lookup);
        result_rec.row += sqrtSize;
        if (result_rec.val <= result.val) result = result_rec;

        result_rec = recursive_partial_monge_min(rowBegin, colBegin + sqrtSize, prefSize, lookup);
        result_rec.col += sqrtSize;
        if (result_rec.val < result.val) result = result_rec;
    }

    return result;
}

min_coords monge_sub_sqr_min(const size_t rowBegin, const size_t colBegin, const size_t size,
                             std::function<int(size_t, size_t)> lookup) {
    return smawk_min(size, size,
                     [&](size_t i, size_t j) -> int { return lookup(rowBegin + i, colBegin + j); });
}
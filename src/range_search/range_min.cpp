#include "range_min.hpp"

RangeMin::RangeMin(int* begin, int* end) {
    // setup table lookup for floor of log_2 for i in range [0, size]
    size_t size = end - begin;
    florLog2lookup = std::vector<int> (size + 1, 0);
    int log2 = 0;
    int pow2 = 1;
    for (int i = 1; i <= size; ++i) {
        while (pow2 * 2 <= i) {
            pow2 *= 2;
            log2 += 1;
        }
        florLog2lookup[i] = log2;
    }

    pow2mins = std::vector<std::vector<int>> (size, std::vector<int>(florLog2lookup[size], 0));
    
    for (int i = 0; i < size; ++i)
        pow2mins[i][0] = *(begin + i);
}

void RangeMin::Initialize() {
    int maxLog2 = florLog2lookup[pow2mins.size()];
    int pow2 = 1;
    for (int log2 = 0; log2 < maxLog2; ++log2) {
        for (size_t i = 0; i + 2 * pow2 <= pow2mins.size(); ++i)
            pow2mins[i][log2+1] = std::min(pow2mins[i][log2], pow2mins[i + pow2][log2]);
        pow2 *= 2;
    }
}

int RangeMin::Min(int beginIdx, int endIdx) {
    int log = florLog2lookup[endIdx - beginIdx + 1];
    int pow = 1 << log;
    return std::min(pow2mins[beginIdx][log], pow2mins[endIdx - pow + 1][log]);
}
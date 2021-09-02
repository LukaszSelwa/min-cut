#include "types.hpp"

bool validate_cuts(const std::vector<bool>& cutA, const std::vector<bool>& cutB) {
    if (cutA.size() != cutB.size()) return false;
    if (cutA.size() == 0) return true;

    bool prev, curr;
    for (size_t i = 1; i < cutA.size(); ++i) {
        prev = cutA[i - 1] == cutB[i - 1];
        curr = cutA[i] == cutB[i];
        if (prev != curr) return false;
    }

    return true;
}
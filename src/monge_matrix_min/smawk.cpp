#include "smawk.hpp"

#include <algorithm>
#include <limits>
#include <numeric>
#include <stack>
#include <vector>

/* ---------------------------------------------------------------*
 *  Implementation based on articles:                             *
 *   1) http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf   *
 *   2) https://www.dannyadam.com/blog/2019/07/smawk-in-cpp/      *
 * ---------------------------------------------------------------*/

void recursive_smawk(std::vector<size_t>& rows, std::vector<size_t>& cols,
                     std::function<int(size_t, size_t)> lookup, std::vector<size_t>& rowsArgmin);

inline void smawk_reduce(std::vector<size_t>& rows, std::vector<size_t>& cols,
                         std::function<int(size_t, size_t)> lookup, std::vector<size_t>& newCols);

void smawk(const size_t numRows, const size_t numCols, std::function<int(size_t, size_t)> lookup,
           std::vector<size_t>& rowsArgmin) {
    std::vector<size_t> rows(numRows);
    std::vector<size_t> cols(numCols);
    std::iota(rows.begin(), rows.end(), 0);
    std::iota(cols.begin(), cols.end(), 0);
    recursive_smawk(rows, cols, lookup, rowsArgmin);
}

int smawk_min(const size_t numRows, const size_t numCols,
              std::function<int(size_t, size_t)> lookup) {
    std::vector<size_t> rowsArgmin(numRows);
    smawk(numRows, numCols, lookup, rowsArgmin);

    int result = std::numeric_limits<int>::max();
    for (size_t row = 0; row < numRows; ++row) {
        size_t argmin = rowsArgmin[row];
        result = std::min(result, lookup(row, argmin));
    }
    return result;
}

void recursive_smawk(std::vector<size_t>& rows, std::vector<size_t>& cols,
                     std::function<int(size_t, size_t)> lookup, std::vector<size_t>& rowsArgmin) {
    if (rows.size() == 0) return;
    std::vector<size_t> newCols(0);
    smawk_reduce(rows, cols, lookup, newCols);

    std::vector<size_t> newRows(0);
    for (size_t idx = 1; idx < rows.size(); idx += 2) {
        newRows.push_back(rows[idx]);
    }
    recursive_smawk(newRows, newCols, lookup, rowsArgmin);

    size_t start = 0, stop;
    size_t cIdx = 0, rIdx;
    size_t row;
    size_t argmin, nextArgmin;
    int min;
    for (rIdx = 0; rIdx < rows.size(); rIdx += 2) {
        row = rows[rIdx];
        stop = newCols.size() - 1;
        if (rIdx < rows.size() - 1) {
            nextArgmin = rowsArgmin[rows[rIdx + 1]];
            while (cIdx + 1 < newCols.size() && newCols[cIdx] != nextArgmin) ++cIdx;
            stop = cIdx;
        }
        argmin = newCols[start];
        min = lookup(row, argmin);
        for (size_t i = start; i <= stop; ++i) {
            int val = lookup(row, newCols[i]);
            if (val < min) {
                min = val;
                argmin = newCols[i];
            }
        }
        rowsArgmin[row] = argmin;
        start = stop;
    }
}

inline void smawk_reduce(std::vector<size_t>& rows, std::vector<size_t>& cols,
                         std::function<int(size_t, size_t)> lookup, std::vector<size_t>& newCols) {
    for (int col : cols) {
        while (!newCols.empty()) {
            size_t head = rows[newCols.size() - 1];
            if (lookup(head, col) >= lookup(head, newCols.back())) break;
            newCols.pop_back();
        }
        if (newCols.size() < rows.size()) newCols.push_back(col);
    }
}
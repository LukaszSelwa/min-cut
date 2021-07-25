#ifndef SMAWK_H
#define SMAWK_H
#include <functional>
#include <iostream>

struct min_coords {
    size_t row, col;
    int val;
    friend bool operator==(const min_coords& a, const min_coords& b);
    friend std::ostream& operator<<(std::ostream& out, const min_coords& m);
};

void smawk(const size_t numRows, const size_t numCols, std::function<int(size_t, size_t)> lookup,
           std::vector<size_t>& rowsArgmin);

min_coords smawk_min(const size_t numRows, const size_t numCols,
                     std::function<int(size_t, size_t)> lookup);

#endif /* SMAWK_H */
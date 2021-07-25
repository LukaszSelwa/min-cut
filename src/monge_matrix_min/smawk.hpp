#ifndef SMAWK_H
#define SMAWK_H
#include <functional>

void smawk(const size_t numRows, const size_t numCols, std::function<int(size_t, size_t)> lookup,
           std::vector<size_t>& rowsArgmin);

int smawk_min(const size_t numRows, const size_t numCols,
              std::function<int(size_t, size_t)> lookup);

#endif /* SMAWK_H */
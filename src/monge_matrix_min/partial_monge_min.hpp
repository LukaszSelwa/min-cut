#ifndef PARTIAL_MONGE_MIN_H
#define PARTIAL_MONGE_MIN_H
#include <functional>

#include "smawk.hpp"

min_coords partial_monge_min(const size_t size, std::function<int(size_t, size_t)> lookup);

#endif /* PARTIAL_MONGE_MIN_H */
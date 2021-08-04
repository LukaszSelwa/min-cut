#include "interval_point_impl.hpp"

template <unsigned N, typename T>
interval_point<N, T>::interval_point(int size) : size(size), begin(0), end(size), val(size) {}

template <unsigned N, typename T>
interval_point<N, T>::interval_point(int size, int begin, int end)
    : size(size), begin(begin), end(end), val(size) {}

template <unsigned N, typename T>
interval_point<N, T>::interval_point() : interval_point(0) {}

template <unsigned N, typename T>
template <typename... COORDS, typename std::enable_if<sizeof...(COORDS) == N - 1, int>::type>
void interval_point<N, T>::add_point(T v, int x0, COORDS... coords) {
    val.add_point(v, coords...);
    if (begin >= end) return;
    int mid = (begin + end) / 2;
    if (x0 <= mid) {
        if (!left) {
            left = std::make_unique<interval_point<N, T>>(size, begin, mid);
        }
        left->add_point(v, x0, coords...);
    }
    if (mid < x0) {
        if (!right) {
            right = std::make_unique<interval_point<N, T>>(size, mid + 1, end);
        }
        right->add_point(v, x0, coords...);
    }
}

template <unsigned N, typename T>
template <typename... COORDS, typename std::enable_if<sizeof...(COORDS) == 2 * N - 2, int>::type>
T interval_point<N, T>::get_sum(int x0, int x1, COORDS... coords) {
    if (x0 <= begin && end <= x1) return val.get_sum(coords...);
    T sum(0);
    int mid = (begin + end) / 2;
    if (x0 <= mid && left) {
        sum += left->get_sum(x0, x1, coords...);
    }
    if (mid < x1 && right) {
        sum += right->get_sum(x0, x1, coords...);
    }
    return sum;
}

template <typename T>
interval_point<0, T>::interval_point(int size) : val(0) {}

template <typename T>
interval_point<0, T>::interval_point(int size, int begin, int end) : val(0) {}

template <typename T>
interval_point<0, T>::interval_point() : interval_point(0) {}

template <typename T>
void interval_point<0, T>::add_point(T v) {
    val += v;
}

template <typename T>
T interval_point<0, T>::get_sum() {
    return val;
}
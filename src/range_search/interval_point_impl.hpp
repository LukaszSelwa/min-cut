#ifndef INTERVAL_POINT_IMPL
#define INTERVAL_POINT_IMPL
#include <memory>
#include <type_traits>
#include <vector>

template <unsigned N, typename T>
class interval_point {
    int size;
    int begin;
    int end;

   public:
    interval_point<N - 1, T> val;
    std::unique_ptr<interval_point> left, right;
    interval_point(int size);
    interval_point(int size, int begin, int end);
    interval_point();

    template <typename... COORDS,
              typename std::enable_if<sizeof...(COORDS) == N - 1, int>::type = 0>
    void add_point(T v, int x0, COORDS... coords);

    template <typename... COORDS,
              typename std::enable_if<sizeof...(COORDS) == 2 * N - 2, int>::type = 0>
    T get_sum(int x0, int x1, COORDS... coords);
};

template <typename T>
class interval_point<0, T> {
    T val;

   public:
    interval_point(int size);
    interval_point(int size, int begin, int end);
    interval_point();
    void add_point(T v);
    T get_sum();
};

#endif /* INTERVAL_POINT_IMPL */
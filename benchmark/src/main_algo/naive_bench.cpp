#include <benchmark/benchmark.h>

#include <algorithm>
#include <memory>
#include <random>

#include "../../../src/graph_generation/random_graph_generation.hpp"
#include "../../../src/main_algo/heuristic_algo.hpp"
#include "../../../src/naive_algo/naive_algo.hpp"

int m_O_n(int n, std::shared_ptr<std::mt19937> seed) {
    int max_m = std::min(n * (n - 1) / 2, 3 * n);
    std::uniform_int_distribution<> distM(n - 1, max_m);
    return distM(*seed);
}

int m_O_n2(int n, std::shared_ptr<std::mt19937> seed) {
    int min_m = std::max(n - 1, n * (n - 1) / 5);
    int max_m = n * (n - 1) / 2;
    std::uniform_int_distribution<> distM(min_m, max_m);
    return distM(*seed);
}

std::shared_ptr<graphs::weighted_graph> generate_naive(size_t n, int type) {
    auto seed = std::make_shared<std::mt19937>();
    size_t m = type == 0 ? m_O_n(n, seed) : m_O_n2(n, seed);
    int maxWeight = n / 2;
    return graphs::generate_random_graph(n, m, maxWeight, seed);
}

static void BM_NaiveAlgo_NaiveGen(benchmark::State& state) {
    auto graph = generate_naive(state.range(1), state.range(0));
    int cut = 0;
    for (auto _ : state) {
        naive::algo algo(graph);
        auto res = algo.calc_min_cut();
        cut = res.minCutVal;
    }
    std::cerr << "Cut val: " << cut << "\n";
}

static void BM_HeuristicAlgo_NaiveGen(benchmark::State& state) {
    auto graph = generate_naive(state.range(1), state.range(0));
    int cut = 0;
    for (auto _ : state) {
        heuristic::algo algo(graph);
        auto res = algo.calc_min_cut();
        cut = res.minCutVal;
    }
    std::cerr << "Cut val: " << cut << "\n";
}

static void CustomArguments(benchmark::internal::Benchmark* b) {
    for (int type = 0; type < 2; ++type)
        for (int n = 50; n <= 300; n += 25) b->Args({type, n});
}

BENCHMARK(BM_NaiveAlgo_NaiveGen)->Apply(CustomArguments);
BENCHMARK(BM_HeuristicAlgo_NaiveGen)->Apply(CustomArguments);
#include <benchmark/benchmark.h>

#include <algorithm>
#include <memory>
#include <random>

#include "../../../src/graph_generation/random_graph_generation.hpp"
#include "../../../src/main_algo/heuristic_algo.hpp"
#include "../../../src/naive_algo/naive_algo.hpp"

std::shared_ptr<graphs::weighted_graph> generate_better(int n, int type) {
    auto seed = std::make_shared<std::mt19937>();
    int minSpTrees, maxSpTrees;
    if (type == 0) {
        minSpTrees = 1;
        maxSpTrees = 4;
    } else {
        minSpTrees = std::max(1, n / 16);
        maxSpTrees = std::max(4, n / 4);
    }
    return graphs::generate_fully_random_graph_input(n, n, 70000, 1, n / 16, seed, type).graph;
}

static void BM_NaiveAlgo_BetterGen(benchmark::State& state) {
    auto graph = generate_better(state.range(1), state.range(0));
    int cut = 0;
    for (auto _ : state) {
        naive::algo algo(graph);
        auto res = algo.calc_min_cut();
        cut = res.minCutVal;
    }
    std::cerr << "Cut val: " << cut << "\n";
}

static void BM_HeuristicAlgo_BetterGen(benchmark::State& state) {
    auto graph = generate_better(state.range(1), state.range(0));
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

BENCHMARK(BM_NaiveAlgo_BetterGen)->Apply(CustomArguments);
BENCHMARK(BM_HeuristicAlgo_BetterGen)->Apply(CustomArguments);
#include <benchmark/benchmark.h>

#include "../../../src/examples/graph_examples.hpp"
#include "../../../src/main_algo/gmw_algo.hpp"
#include "../../../src/main_algo/karger_algo.hpp"

template <class ALGO>
void run_example(int id) {
    auto example = examples::get_example(id);
    ALGO algo(example.graph, example.spanningTree);
    algo.initialize();
    auto res = algo.find_cut();
}

static void BM_GMW_GraphExamples(benchmark::State& state) {
    for (auto _ : state) run_example<gmw_algo>(state.range(0));
}

static void BM_Karger_GraphExamples(benchmark::State& state) {
    for (auto _ : state) run_example<karger_algo>(state.range(0));
}

BENCHMARK(BM_GMW_GraphExamples)->DenseRange(1, 5, 1);
BENCHMARK(BM_Karger_GraphExamples)->DenseRange(1, 5, 1);
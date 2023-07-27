#include <benchmark/benchmark.h>
#include <libSimpleScanner.h>

static void BM_SimpleScanner(benchmark::State &state) {

    for (auto _ : state) {
    }
}

// Register the function as a benchmark
BENCHMARK(BM_SimpleScanner);

// Run the benchmark
BENCHMARK_MAIN();

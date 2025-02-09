#include <iostream>
#include <vector>
#include <benchmark/benchmark.h>

constexpr size_t DATA_SIZE = 10000;

void slowFunction()
{
    std::vector<int32_t> data;
    for (size_t i = 0; i < DATA_SIZE; i++)
    {
        data.push_back(int32_t(i));
    }
}

void fastFunction()
{
    std::vector<int32_t> data(DATA_SIZE);
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] = int32_t(i);
    }
}

static void BM_slowFunction(benchmark::State &state)
{
    // Perform setup here
    for (auto _ : state)
    {
        // This code gets timed
        slowFunction();
    }
}

static void BM_fastFunction(benchmark::State &state)
{
    // Perform setup here
    for (auto _ : state)
    {
        // This code gets timed
        fastFunction();
    }
}

// Register the functions as a benchmark
BENCHMARK(BM_slowFunction);
BENCHMARK(BM_fastFunction);

// Run the benchmark
BENCHMARK_MAIN();

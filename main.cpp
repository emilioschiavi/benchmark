#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <benchmark/benchmark.h>

constexpr size_t DATA_SIZE = 10000;
constexpr size_t MAP_SIZE = 1000000;

std::unordered_map<std::string, int32_t> s_unordered_map;
std::map<std::string, int32_t> s_map;

void createMaps()
{
    for (size_t i = 0; i < MAP_SIZE; i++)
    {
        s_unordered_map[std::to_string(i)] = i;
        s_map[std::to_string(i)] = i;
    }
}

static void DoSetup([[maybe_unused]] const benchmark::State &state)
{
    static bool callSetup = true;
    if (callSetup)
    {
        createMaps();
        callSetup = false;
    }
}

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

void stlFunction()
{
    std::vector<int32_t> data(DATA_SIZE);
    int32_t counter = 0;
    std::generate(data.begin(), data.end(), [&]()
                  { return counter++; });
}

void mapFnc()
{
    const auto &it1 = s_map.find("1");
    if (it1->second != 1)
    {
        assert(false);
    }
}

void unordered_mapFnc()
{
    const auto &it1 = s_unordered_map.find("1");
    if (it1->second != 1)
    {
        assert(false);
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

static void BM_stlFunction(benchmark::State &state)
{
    // Perform setup here
    for (auto _ : state)
    {
        // This code gets timed
        stlFunction();
    }
}

static void BM_map(benchmark::State &state)
{
    // Perform setup here
    for (auto _ : state)
    {
        // This code gets timed
        mapFnc();
    }
}

static void BM_unordered_map(benchmark::State &state)
{
    // Perform setup here
    for (auto _ : state)
    {
        // This code gets timed
        unordered_mapFnc();
    }
}

// Register the functions as a benchmark
BENCHMARK(BM_slowFunction);
BENCHMARK(BM_fastFunction);
BENCHMARK(BM_stlFunction);
BENCHMARK(BM_map)->Setup(DoSetup);
BENCHMARK(BM_unordered_map)->Setup(DoSetup);

// Run the benchmark
BENCHMARK_MAIN();

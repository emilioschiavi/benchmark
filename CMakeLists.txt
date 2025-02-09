cmake_minimum_required(VERSION 3.23)
project(test_benchmark)

include(FetchContent)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.9.1
)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

FetchContent_MakeAvailable(
  googletest
  googlebenchmark
)

add_executable(main main.cpp)
target_compile_options(main PRIVATE -std=c++17 -Wall -Wextra)
target_link_libraries(main PRIVATE benchmark::benchmark)

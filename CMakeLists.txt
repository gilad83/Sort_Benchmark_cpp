cmake_minimum_required(VERSION 3.17)
project(Sort_Benchmark_cpp)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-std=c++11)

add_executableSort_Benchmark_cpp main.cpp SortAlgos.cpp SortAlgos.h)
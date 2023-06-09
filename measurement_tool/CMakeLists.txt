cmake_minimum_required(VERSION 3.22)
project(measurement_tool)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(measurement_tool main.cpp algorithms/algorithms.cpp algorithms/algorithms.h utils/time_it.h utils/substitute_inject.h)

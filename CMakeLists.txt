cmake_minimum_required(VERSION 3.2)
project(Algo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Algo ${SOURCE_FILES} sort_algo.hpp iter_traits.hpp)

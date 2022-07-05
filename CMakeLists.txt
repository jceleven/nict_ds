cmake_minimum_required(VERSION 3.0)

project(nict_ds)

set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(include)

add_executable(sparse_matrix src/sparse_matrix.cpp)

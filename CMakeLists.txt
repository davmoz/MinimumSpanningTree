cmake_minimum_required(VERSION 3.10)
project(Lists)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lists main.cpp List.h AdjacencyInfo.h AdjacencyInfo.cpp Graph.cpp Graph.h)
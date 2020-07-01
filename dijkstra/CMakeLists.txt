cmake_minimum_required (VERSION 2.56)
project (dijkstra)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_executable (dijkstra main.c dijkstra.c)

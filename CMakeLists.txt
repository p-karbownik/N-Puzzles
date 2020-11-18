cmake_minimum_required(VERSION 3.17)
project(Npuzzles)

set(CMAKE_CXX_STANDARD 14)

add_executable(Npuzzles src/main.cpp src/BFS_solver.cpp src/BFS_solver.hpp)
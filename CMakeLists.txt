cmake_minimum_required(VERSION 3.17)
project(Npuzzles)

set(CMAKE_CXX_STANDARD 14)

add_executable(Npuzzles src/main.cpp src/A_star_solver.cpp src/A_star_solver.h)
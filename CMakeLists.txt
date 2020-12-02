cmake_minimum_required(VERSION 3.17)
project(Npuzzles)

set(CMAKE_CXX_STANDARD 14)

add_executable(Npuzzles src/main.cpp src/A_star_solver.cpp src/A_star_solver.h src/BFS_solver.cpp src/BFS_solver.hpp src/Pattern_generator.cpp src/Pattern_generator.hpp src/Solvability_verifier.cpp src/Solvability_verifier.hpp src/FileInputReader.cpp src/FileInputReader.h src/Solution_printer.cpp src/Solution_printer.hpp)


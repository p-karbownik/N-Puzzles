#include <iostream>
#include <vector>
#include "A_star_solver.h"


int main()
{
    std::vector<std::vector<int>> board;
    board.push_back({0, 1, 3});
    board.push_back({4, 2, 5});
    board.push_back({7, 8, 6});
    auto solver = new A_star_solver(board);
    std::cout << solver->solve() << std::endl;
    solver->printSolution();
    return 0;
}

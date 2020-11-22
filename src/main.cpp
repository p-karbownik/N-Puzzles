#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include "A_star_solver.h"


int main()
{
    std::vector<std::vector<int>> board =
            {
                    {5, 3, 8, 13},
                    {9, 2, 4, 0},
                    {14, 7, 12, 6},
                    {10, 15, 11, 1}
            };
    auto solver = new A_star_solver(board);
    std::cout << solver->solve() << std::endl;
    solver->printSolution();
    return 0;
}

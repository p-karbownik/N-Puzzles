#include <iostream>
#include <vector>
#include <set>
#include "A_star_solver.h"


int main()
{
    std::vector<std::vector<int>> board =
            {
                    {5, 9, 3, 4},
                    {6, 10, 14, 8},
                    {0, 13, 2, 15},
                    {11, 7, 12, 1}
            };
    auto solver = new A_star_solver(board);
    clock_t start = clock();
    std::cout << solver->solve() << std::endl;
    std::cout << "czas wykonania " << ( clock() - start ) / CLOCKS_PER_SEC<< std::endl;
    solver->printSolution();
    //std::cout << 5861044965 / CLOCKS_PER_SEC;
    return 0;
}

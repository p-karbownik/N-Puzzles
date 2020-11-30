#include <iostream>
#include<vector>
#include <set>
#include"BFS_solver.hpp"
#include "A_star_solver.h"

using namespace std;

int main()
{
    std::cout << "Hello, World!!!" << std::endl;

    vector<vector<int> > testV = {
        {-1, 1, 3},
        { 4, 2, 5},
        { 7, 8, 6}
    };
    BFS_solver solver1 = BFS_solver(testV);
    solver1.solve();
  
    std::vector<std::vector<int>> board =
            {
                    {5, 9, 3, 4},
                    {6, 10, 14, 8},
                    {0, 13, 2, 15},
                    {11, 7, 12, 1}
            };
    auto solver2 = new A_star_solver(board);
    clock_t start = clock();
    std::cout << solver2->solve() << std::endl;
    std::cout << "czas wykonania " << ( clock() - start ) / CLOCKS_PER_SEC<< std::endl;
    solver2->printSolution();
    //std::cout << 5861044965 / CLOCKS_PER_SEC;

    return 0;
}

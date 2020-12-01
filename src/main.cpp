#include <iostream>
#include <vector>
#include <set>

#include"BFS_solver.hpp"
#include "A_star_solver.h"

using namespace std;

int main(int argc, char **argv)
{

    if(argc == 4)
    {
        //*generowanie itd
        int mode = atoi(argv[1]);
        bool displayPath = atoi(argv[2]) == 1;

    }
    else if(argc == 1)
    {

    }
    */
   /* std::cout << "Hello, World!!!" << std::endl;
    clock_t start = clock();
    vector<vector<int> > testV = {
            {2, 5, 3, 4},
            {9, 1, 7, 8},
            {-1, 6, 10, 12},
            {13, 14, 11, 15}
    };
    BFS_solver solver1 = BFS_solver(testV);
    solver1.solve();
    std::cout << "czas wykonania " << ( clock() - start ) / CLOCKS_PER_SEC<< std::endl;

    std::vector<std::vector<int>> board =
            {
                    {2, 5, 3, 4},
                    {9, 1, 7, 8},
                    {-1, 6, 10, 12},
                    {13, 14, 11, 15}
            };
    auto solver2 = new A_star_solver(board);
    auto start = clock();
    std::cout << solver2->solve() << std::endl;
    std::cout << "czas wykonania " << ( clock() - start ) / CLOCKS_PER_SEC<< std::endl;
    solver2->printSolution();
    return 0;
}

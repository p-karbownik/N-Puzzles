#include <iostream>
#include <vector>
#include <set>

#include "BFS_solver.hpp"
#include "A_star_solver.h"
#include "Pattern_generator.hpp"

using namespace std;

int main(int argc, char** argv)
{

    if(argc == 4)
    {
        /* parametry: dimension, solver, displayPath */
        int dimension = atoi(argv[1]);
        Pattern_generator generator;
        vector<vector<int> > testV;
        generator.generate(testV, dimension * dimension - 1);

        std::cout << "Wyegenerowany przypadek" << std::endl;
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                cout << testV[i][j] << " ";
            }
            cout << endl;
        }

        bool displayPath = atoi(argv[3]) == 1;
        int whichSolver = atoi(argv[2]); /* 0 - BFS, 1 - A*, 2 - both */

        if(whichSolver == 0 || whichSolver == 2)
        {
            std::cout << "Szukanie rozwiazania przy uzyciu BFS" << std::endl;
            BFS_solver solver1 = BFS_solver(testV);
            solver1.solve();
            /* drukowanie statystyki*/

            if(displayPath)
            {  }// wyswietl Path}
        }

        if(whichSolver == 1 || whichSolver == 2)
        {

            auto solver2 = new A_star_solver(testV);
            solver2->solve();
            /*drukowanie statystyki */
            if(displayPath)
            {
                solver2->printSolution();
            }
            delete solver2;
        }
    }
    // std::cout << "Hello, World!!!" << std::endl;

    // vector<vector<int> > testV = {
    //     {-1, 1, 3},
    //     { 4, 2, 5},
    //     { 7, 8, 6}
    // };
    // BFS_solver solver1 = BFS_solver(testV);
    // solver1.solve();
  
    // std::vector<std::vector<int>> board =
    //         {
    //                 {5, 9, 3, 4},
    //                 {6, 10, 14, 8},
    //                 {0, 13, 2, 15},
    //                 {11, 7, 12, 1}
    //         };
    // auto solver2 = new A_star_solver(testV);
    // clock_t start = clock();
    // std::cout << solver2->solve() << std::endl;
    // std::cout << "czas wykonania " << ( clock() - start ) / CLOCKS_PER_SEC<< std::endl;
    // solver2->printSolution();
    // std::cout << 5861044965 / CLOCKS_PER_SEC;

    return 0;
}

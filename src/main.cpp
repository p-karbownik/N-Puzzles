#include <iostream>
#include <vector>
#include <set>

#include "BFS_solver.hpp"
#include "A_star_solver.h"
#include "Pattern_generator.hpp"
#include "FileInputReader.h"
#include "Solution_printer.hpp"

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

        std::cout << "Wygenerowany przypadek" << std::endl;
        Solution_printer::print_grid(testV);

        bool displayPath = atoi(argv[3]) == 1;
        int whichSolver = atoi(argv[2]); /* 0 - BFS, 1 - A*, 2 - both */

        if(whichSolver == 0 || whichSolver == 2)
        {
            std::cout << "Szukanie rozwiazania przy uzyciu BFS" << std::endl;
            BFS_solver solver1 = BFS_solver(testV);
            solver1.solve();
            auto solution = solver1.get_solution();
            
            std::cout << "Czas: " << solver1.getDuration().count() << " Iteracje pętli: " << solver1.getLoopIterations() << std::endl;

            if(displayPath)
            {
                Solution_printer::print_solution(solution);
            }
        }

        if(whichSolver == 1 || whichSolver == 2)
        {

            auto solver2 = new A_star_solver(testV);
            auto solution = solver2->solve();

            std::cout << "Czas: " << solver2->getDuration().count() << " Iteracje pętli: " << solver2->getLoopIterations() << std::endl;

            if(displayPath)
            {
                Solution_printer::print_solution(solution);
            }

            delete solver2;
        }
    }
    else if (argc == 1)
    {
        FileInputReader fir = FileInputReader("wej.txt");
        fir.read();

        for(int i = 0; i < fir.getPuzzlesAmount(); i++)
        {
            if(fir.getWhichSolver() == 0 || fir.getWhichSolver() == 2)
            {
                std::cout << "Szukanie rozwiazania przy uzyciu BFS" << std::endl;
                BFS_solver solver1 = BFS_solver(fir.getPuzzleToSolve());
                if (!solver1.solve())
                    cout << "Rozwiązanie nie jest możliwe";

                std::cout << "Czas: " << solver1.getDuration().count() << " Iteracje pętli: " << solver1.getLoopIterations() << std::endl;

                auto solution = solver1.get_solution();

                if(fir.getDisplayPath())
                {
                    Solution_printer::print_solution(solution) ;
                }
            }
            if(fir.getWhichSolver() == 1 || fir.getWhichSolver() == 2)
            {
                std::cout << "Szukanie rozwiazania przy uzyciu A*" << std::endl;

                auto solver2 = new A_star_solver(fir.getPuzzleToSolve());
                auto solution = solver2->solve();

                std::cout << "Czas: " << solver2->getDuration().count() << " Iteracje pętli: " << solver2->getLoopIterations() << std::endl;

                if(fir.getDisplayPath())
                {
                    Solution_printer::print_solution(solution) ;
                }

                delete solver2;
            }
            fir.setNextPuzzle();
        }
    }

    return 0;
}

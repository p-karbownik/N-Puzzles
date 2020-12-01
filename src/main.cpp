#include <iostream>
#include <vector>
#include <set>

#include "BFS_solver.hpp"
#include "A_star_solver.h"
#include "Pattern_generator.hpp"
#include "FileInputReader.h"

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
            auto vect = solver2->solve();
            /*drukowanie statystyki */
            if(displayPath)
            {
                std::cout << std::endl;
                for(int i = 0; i < vect.size(); i++)
                {
                    std::cout << "i = " << i << std::endl;
                    for(int j = 0; j < vect[0].size(); j++)
                    {
                        for(int k = 0; k < vect[0].size(); k++)
                            std::cout << vect[i][j][k] << " ";
                        std::cout << std::endl;
                    }
                    /* funkcja drukowania */
                }
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
                solver1.solve();
                /* drukowanie statystyki*/

                if(fir.getDisplayPath())
                {  }// wyswietl Path}
            }
            if(fir.getWhichSolver() == 1 || fir.getWhichSolver() == 2)
            {

                auto solver2 = new A_star_solver(fir.getPuzzleToSolve());
                auto vect = solver2->solve();
                std::cout << fir.getDisplayPath();
                if(fir.getDisplayPath())
                {
                    std::cout << std::endl;
                    for(int i = 0; i < vect.size(); i++)
                    {
                        std::cout << "i = " << i << std::endl;
                        for(int j = 0; j < vect[0].size(); j++)
                        {
                            for(int k = 0; k < vect[0].size(); k++)
                                std::cout << vect[i][j][k] << " ";
                            std::cout << std::endl;
                        }
                    /* funkcja drukowania */
                    }
                }
                delete solver2;
            }
            fir.setNextPuzzle();
        }
    }

    return 0;
}

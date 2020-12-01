#ifndef NPUZZLES_SOLUTION_PRINTER
#define NPUZZLES_SOLUTION_PRINTER

#include<vector>

class Solution_printer {
public:
    void print_grid(std::vector<std::vector<int> > &grid);
    void print_solution(std::vector<std::vector<std::vector<int> > > &solution);
};

#endif //NPUZZLES_SOLUTION_PRINTER
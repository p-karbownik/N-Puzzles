#include <iostream>
#include <iomanip>

#include "Solution_printer.hpp"

using namespace std;

void Solution_printer::print_grid(vector<vector<int> > &grid) {
    for(int j = 0; j < grid.size(); j++)
    {
        for(int k = 0; k < grid[0].size(); k++)
            cout << setw(2) << grid[j][k] << " ";
        cout << endl;
    }
}

void Solution_printer::print_solution(vector<vector<vector<int> > > &solution) {
    cout << endl;
    for(int i = 0; i < solution.size(); i++) {   
        cout << "i = " << i << endl;
        print_grid(solution[i]);
        cout << endl;
    }
}
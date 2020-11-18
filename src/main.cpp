#include <iostream>
#include<vector>
#include"BFS_solver.hpp"

int main()
{
    std::cout << "Hello, World!!!" << std::endl;

    vector<vector<int> > testV = {
         {5, 1, 7, 3},
        {-1, 2,11, 4},
        { 9, 6,15, 8},
        {13,10,14,12}
    };
    BFS_solver solver = BFS_solver(testV);
    solver.BFS();

    return 0;
}

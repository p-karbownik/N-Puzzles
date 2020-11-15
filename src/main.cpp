#include <iostream>
#include<vector>
#include"BFS_solver.hpp"

int main()
{
    std::cout << "Hello, World!!!" << std::endl;

    vector<vector<int> > testV = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12},
        {13,14,-1,15}
    };
    BFS_solver solver = BFS_solver(testV);
    solver.BFS();

    return 0;
}

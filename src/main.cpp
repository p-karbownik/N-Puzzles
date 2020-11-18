#include <iostream>
#include<vector>
#include"BFS_solver.hpp"

using namespace std;

int main()
{
    std::cout << "Hello, World!!!" << std::endl;

    vector<vector<int> > testV = {
        {-1, 1, 3},
        { 4, 2, 5},
        { 7, 8, 6}
    };
    BFS_solver solver = BFS_solver(testV);
    solver.BFS();

    return 0;
}

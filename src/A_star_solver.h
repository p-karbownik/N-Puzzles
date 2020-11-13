//
// Created by patryk on 10.11.2020.
//

#ifndef NPUZZLES_A_STAR_SOLVER_H
#define NPUZZLES_A_STAR_SOLVER_H

#include <vector>
#include <cstdlib>

class A_star_solver
{
private:
    struct Node
    {
        std::vector<std::vector<int>> n_puzzle_array;
        bool isVisited;
        int f_value;
        int g_value;
        int h_value;
    };

    Node* root;
    int calculateManhattanDistanceValue(Node* node);
    int calculateLinearConflictsValue(Node* node);
    int calculateHValue(Node* node);
    int dimension;
public:
    A_star_solver(std::vector<std::vector<int>> root_array);
    void solve();
};


#endif //NPUZZLES_A_STAR_SOLVER_H

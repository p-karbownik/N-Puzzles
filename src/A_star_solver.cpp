//
// Created by patryk on 10.11.2020.
//

#include "A_star_solver.h"

int A_star_solver::calculateHValue(Node *node)
{
    return calculateManhattanDistanceValue(node) + 2 * calculateLinearConflictsValue(node);
}

int A_star_solver::calculateManhattanDistanceValue(Node *node)
{
    int manhattanDistanceValue = 0;
    int expectedValue = 0;
    int expectedRow, expectedColumn;

    for (int i = 0; i < dimension; i++)
        for(int j = 0; j < dimension; j++)
        {
            expectedValue++;
            
            if(node->n_puzzle_array[i][j] == expectedValue || node->n_puzzle_array[i][j] == 0)
            {
                continue;
            }
            else
            {
                expectedColumn = (node->n_puzzle_array[i][j] - 1) % dimension;
                expectedRow = (node->n_puzzle_array[i][j] - 1) / dimension;

                manhattanDistanceValue += abs(expectedRow - i) + abs(expectedColumn - j);
            }
        }

    return manhattanDistanceValue;
}

int A_star_solver::calculateLinearConflictsValue(Node *node)
{
    int linearConflictsValue = 0;
    int expectedValue = 0;
    int expectedColumn, expectedRow;
    for(int i = 0; i < dimension; i++)
        for(int j = 0; j < dimension; j++)
        {
            expectedValue++;
            expectedColumn = (node->n_puzzle_array[i][j] - 1) % dimension;
            expectedRow = (node->n_puzzle_array[i][j] - 1) / dimension;

            bool isPossibilityOfLinearConflict = ((abs(expectedColumn - j) == 1) && expectedRow == i) || (abs((expectedRow - 1) - i) == 1 && expectedColumn == j);

            if(node->n_puzzle_array[i][j] == expectedValue || node->n_puzzle_array[i][j] == 0 || !isPossibilityOfLinearConflict)
                continue;
            else
            {
                if((j + 1) != dimension && node->n_puzzle_array[i][j + 1] != 0)
                {
                    if(node->n_puzzle_array[i][j] - node->n_puzzle_array[i][j] == 1)
                    {
                        linearConflictsValue++;
                        expectedValue++;
                        j++;

                        continue;
                    }
                }

                if((i + 1) != dimension && node->n_puzzle_array[i + 1][j] != 0)
                {
                    if(node->n_puzzle_array[i][j] - node->n_puzzle_array[i + 1][j] ==  dimension)
                        linearConflictsValue++;
                }
            }
        }

    return linearConflictsValue;
}
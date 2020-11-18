//
// Created by patryk on 10.11.2020.
//

#include <set>
#include <queue>
#include <utility>
#include <iostream>
#include "A_star_solver.h"

A_star_solver::Node::Node()
{
    isVisited = false;
    f_value = 0;
    g_value = 0;
    h_value = 0;
    blank_field_column = -1;
    blank_field_row = -1;
}

A_star_solver::Node::Node(std::vector<std::vector<int>> n_puzzle_array)
{
    this->n_puzzle_array = std::move(n_puzzle_array);
    isVisited = false;
    f_value = 0;
    g_value = 0;
    h_value = 0;

    for(int i = 0; i < this->n_puzzle_array.size(); i++)
        for(int j = 0; j < this->n_puzzle_array.size(); j++)
        {
            if(this->n_puzzle_array[i][j] == 0)
            {
                blank_field_column = j;
                blank_field_row = i;
            }
        }
}

A_star_solver::Node::Node(const Node &node)
{
    n_puzzle_array = node.n_puzzle_array;
    isVisited = node.isVisited;
    f_value = node.f_value;
    g_value = node.g_value;
    h_value = node.h_value;
    blank_field_row = node.blank_field_row;
    blank_field_column = node.blank_field_column;
}

A_star_solver::Node::Node(int dimension)
{
    int x = 1;

    std::vector<std::vector<int>> board;
    for(int i = 0; i < dimension; i++)
    {
        std::vector<int> row;
        for (int j = 0; j < dimension; j++)
        {
            if( (i + 1) * (j + 1) == dimension * dimension)
            {
                row.push_back(0);
            }
            else
                row.push_back(x++);
        }
        board.push_back(row);
    }
    this->n_puzzle_array = board;
    this->g_value = 0;
    this->f_value = 0;
    this->h_value = 0;
    this->isVisited = false;
    this->blank_field_column = dimension - 1;
    this->blank_field_row = dimension - 1;
}


bool A_star_solver::Node::operator<(const Node &node) const
{
    return this->f_value < node.f_value;
}

bool A_star_solver::Node::operator>(const Node &node) const
{
    return !(this->operator<(node));
}

bool A_star_solver::Node::operator==(const Node &node) const
{
    return this->f_value == this->h_value;
}

A_star_solver::Node* A_star_solver::Node::getNeighbour(int direction)
{
    Node* x = new Node(*this);

    switch (direction)
    {
        case 0: /*UP*/
            if(this->blank_field_row - 1 < 0)
            break;

            x->n_puzzle_array[x->blank_field_row][x->blank_field_column] = x->n_puzzle_array[x->blank_field_row - 1][x->blank_field_column];
            x->n_puzzle_array[x->blank_field_row - 1][x->blank_field_column] = 0;
            x->blank_field_row -= 1;

            return x;
            break;
        case 1: /*RIGHT*/
            if(this->blank_field_column + 1 >= this->n_puzzle_array.size())
                break;

            x->n_puzzle_array[x->blank_field_row][x->blank_field_column] = x->n_puzzle_array[x->blank_field_row][x->blank_field_column + 1];
            x->n_puzzle_array[x->blank_field_row][x->blank_field_column + 1] = 0;
            x->blank_field_column += 1;

            return x;
            break;
        case 2: /*DOWN*/
            if(this->blank_field_row + 1 >= this->n_puzzle_array.size())
                return nullptr;

            x->n_puzzle_array[x->blank_field_row][x->blank_field_column] = x->n_puzzle_array[x->blank_field_row + 1][x->blank_field_column];
            x->n_puzzle_array[x->blank_field_row + 1][x->blank_field_column] = 0;
            x->blank_field_row += 1;

            return x;
            break;
        case 3: /*LEFT*/
            if(this->blank_field_column - 1 < 0)
                return nullptr;

            x->n_puzzle_array[x->blank_field_row][x->blank_field_column] = x->n_puzzle_array[x->blank_field_row][x->blank_field_column - 1];
            x->n_puzzle_array[x->blank_field_row][x->blank_field_column - 1] = 0;
            x->blank_field_column -= 1;

            return x;
            break;
        default:
            break;
    }
    delete x;
    return nullptr;
}

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

bool A_star_solver::checkNodeInVector(Node *node, std::vector<Node *> &vector)
{
    for(auto & i : vector)
    {
        if(node->n_puzzle_array == i->n_puzzle_array)
            return true;
    }

    return false;
}

bool A_star_solver::solve()
{
    std::vector<Node*> chosenNodes; // zbior wierzcholkow przejrzanych
    std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int,Node*>>, std::greater<std::pair<int, Node*>>> openList; //zbior wierzcholkow nieodwiedzonych, sasiadujacych z odwiedzonymi

    chosenNodes.push_back(root);
    Node* x = root;
    int actual_g = 0;

    while(x != nullptr)
    {
        actual_g++;
        if(x->n_puzzle_array == goal->n_puzzle_array)
        {
            // obsluga znalezienia wyniku
            pathToGoal = chosenNodes;
            return true;
        }

        for(int i = 0; i < 4; i++)
        {
            Node* y = x->getNeighbour(i);

            if(y == nullptr)
            {
                continue;
            }

            if(checkNodeInVector(y, chosenNodes))
            {
                delete y;

                continue;
            }

            y->h_value = calculateHValue(y);
            y->g_value = actual_g;
            y->f_value = y->g_value + y->h_value;

            /*sprawdz, czy element o tym priorytecie jest juz w kolejce*/
            /*jesli jest to delete & continue */
            /*jesli nie ma to dodaj */
            openList.push(std::make_pair(y->f_value, y));

        }

        if(openList.empty())
        {
            break;
        }

        x = openList.top().second;
        openList.pop();

        chosenNodes.push_back(x);

        for(int i = 0; i < openList.size(); i++)
        {
            delete openList.top().second;
            openList.pop();
        }
        pathToGoal = chosenNodes;

    }

    return false;
}

void A_star_solver::printSolution()
{
    for(int i = 0; i < pathToGoal.size(); i++)
    {
        std::cout << "i = " << i << std::endl;
        for(int j = 0; j < dimension; j++)
        {
            for(int k = 0; k < dimension; k++)
                std::cout << pathToGoal[i]->n_puzzle_array[j][k] << " ";
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
}
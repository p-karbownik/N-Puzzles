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
    parent = nullptr;
}

A_star_solver::Node::Node(std::vector<std::vector<int>> n_puzzle_array)
{
    this->n_puzzle_array = n_puzzle_array;
    isVisited = false;
    f_value = 0;
    g_value = 0;
    h_value = 0;
    parent = nullptr;
    for(int i = 0; i < this->n_puzzle_array.size(); i++)
        for(int j = 0; j < this->n_puzzle_array.size(); j++)
        {
            if(this->n_puzzle_array[i][j] == -1)
            {
                blank_field_column = j;
                blank_field_row = i;
            }
        }
}

A_star_solver::Node::Node(const Node &node)
{
    n_puzzle_array = node.n_puzzle_array;
    parent = node.parent;
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
                row.push_back(-1);
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
    this->parent = nullptr;
}

A_star_solver::Node* A_star_solver::Node::getNeighbour(int direction)
{
    Node* x = new Node(*this);

    switch (direction)
    {
        case 0: /*UP*/
            if(this->blank_field_row - 1 < 0)
            {
                delete x;
                return nullptr;
            }
            x->n_puzzle_array[x->blank_field_row][x->blank_field_column] = x->n_puzzle_array[x->blank_field_row - 1][x->blank_field_column];
            x->n_puzzle_array[x->blank_field_row - 1][x->blank_field_column] = -1;
            x->blank_field_row -= 1;

            return x;
            break;
        case 1: /*RIGHT*/
            if(this->blank_field_column + 1 >= this->n_puzzle_array.size())
            {
                delete x;
                return nullptr;
            }

            x->n_puzzle_array[x->blank_field_row][x->blank_field_column] = x->n_puzzle_array[x->blank_field_row][x->blank_field_column + 1];
            x->n_puzzle_array[x->blank_field_row][x->blank_field_column + 1] = -1;
            x->blank_field_column += 1;

            return x;
            break;
        case 2: /*DOWN*/
            if(this->blank_field_row + 1 >= this->n_puzzle_array.size())
            {
                delete x;
                return nullptr;
            }

            x->n_puzzle_array[x->blank_field_row][x->blank_field_column] = x->n_puzzle_array[x->blank_field_row + 1][x->blank_field_column];
            x->n_puzzle_array[x->blank_field_row + 1][x->blank_field_column] = -1;
            x->blank_field_row += 1;

            return x;
            break;
        case 3: /*LEFT*/
            if(this->blank_field_column - 1 < 0)
            {
                delete x;
                return nullptr;
            }

            x->n_puzzle_array[x->blank_field_row][x->blank_field_column] = x->n_puzzle_array[x->blank_field_row][x->blank_field_column - 1];
            x->n_puzzle_array[x->blank_field_row][x->blank_field_column - 1] = -1;
            x->blank_field_column -= 1;

            return x;
            break;
        default:
            break;
    }
    delete x;
    return nullptr;
}

void A_star_solver::Node::setHValue()
{
    this->h_value = calculateManhattanDistanceValue() + 2 * calculateLinearConflictsValue();
}

int A_star_solver::Node::calculateManhattanDistanceValue()
{
    int manhattanDistanceValue = 0;
    int expectedValue = 0;
    int expectedRow, expectedColumn;
    int dimension = this->n_puzzle_array.size();

    for (int i = 0; i < dimension; i++)
        for(int j = 0; j < dimension; j++)
        {
            expectedValue++;
            
            if(this->n_puzzle_array[i][j] == expectedValue || this->n_puzzle_array[i][j] == -1)
            {
                continue;
            }
            else
            {
                expectedColumn = (this->n_puzzle_array[i][j] - 1) % dimension;
                expectedRow = (this->n_puzzle_array[i][j] - 1) / dimension;

                manhattanDistanceValue += abs(expectedRow - i) + abs(expectedColumn - j);
            }
        }

    return manhattanDistanceValue;
}

int A_star_solver::Node::calculateLinearConflictsValue()
{
    int linearConflictsValue = 0;
    int expectedValue_j, expectedValue_k;
    int dimension = this->n_puzzle_array.size();

    for (int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
            for(int k = j + 1; k < dimension; k++)
            {
                if(this->n_puzzle_array[i][j] == -1 || this->n_puzzle_array[i][k] == -1)
                    continue;

                expectedValue_j = (this->n_puzzle_array[i][j] - 1) / dimension;
                expectedValue_k = (this->n_puzzle_array[i][k] - 1) / dimension;

                if(expectedValue_j != i || i != expectedValue_k)
                    continue;

                if(expectedValue_k != expectedValue_j)
                    continue;

                expectedValue_j = (this->n_puzzle_array[i][j] - 1) % dimension;
                expectedValue_k = (this->n_puzzle_array[i][k] - 1) % dimension;

                if(expectedValue_k < expectedValue_j)
                    linearConflictsValue++;
            }
    }

    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            for(int k = j + 1; k < dimension; k++)
            {
                if(this->n_puzzle_array[i][j] == -1 || this->n_puzzle_array[i][k] == -1)
                    continue;

                expectedValue_j = (this->n_puzzle_array[i][j] - 1) % dimension;
                expectedValue_k = (this->n_puzzle_array[i][k] - 1) % dimension;


                if(expectedValue_j != i || i != expectedValue_k)
                    continue;

                if(expectedValue_k != expectedValue_j)
                    continue;

                expectedValue_j = (this->n_puzzle_array[i][j] - 1) / dimension;
                expectedValue_k = (this->n_puzzle_array[i][k] - 1) / dimension;

                if(expectedValue_k < expectedValue_j)
                    linearConflictsValue++;
            }

    return linearConflictsValue;
}

bool A_star_solver::isInClosedList(Node* node, std::vector<Node*> &closedSet)
{
    for(int i = 0; i < closedSet.size(); i++)
    {
        if(closedSet.at(i)->n_puzzle_array == node->n_puzzle_array)
            return true;
    }
    return false;
}
A_star_solver::Node* A_star_solver::getFromOpenSet(Node *node, std::multiset<std::pair<int, Node *>> set)
{

    for(auto iter = set.begin(); iter != set.end(); iter++)
    {
        if(iter->second->n_puzzle_array == node->n_puzzle_array)
            return iter->second;
    }
    return nullptr;
}

std::vector<std::vector<std::vector<int>>> A_star_solver::solve()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::multiset<std::pair<int, Node*>> openList; //zbior wierzcholkow nieodwiedzonych, sasiadujacych z odwiedzonymi
    std::vector<Node*> closedList; //zbior wierzcholkow przejrzanych

    root->setHValue();
    root->g_value = 0;
    root->f_value = root->h_value + root->g_value;

    openList.insert(std::make_pair(root->f_value, root));

    while(!openList.empty())
    {
        Node* x = openList.begin()->second;

        if(x->n_puzzle_array == goal->n_puzzle_array)
        {
            openList.erase(openList.begin());
            reconstructPath(x);
            break;
        }

        openList.erase(openList.begin());
        closedList.push_back(x);

        for(int i = 0; i < 4; i++)
        {
            Node* y = x->getNeighbour(i);

            if(y == nullptr)
            {
                continue;
            }

            if(isInClosedList(y, closedList))
            {
                delete y;
                continue;
            }

            int temp_g = x->g_value + 1;

            Node* y_fromOpenList = getFromOpenSet(y, openList);
            bool tentative_is_better = false;

            if(y_fromOpenList == nullptr)
            {
                y->setHValue();
                y->g_value = temp_g;
                y->f_value = y->h_value + y->g_value;
                openList.insert(std::make_pair(y->f_value, y));
                tentative_is_better = true;
            }
            else if(temp_g < y_fromOpenList->g_value)
            {
                delete y;
                y = y_fromOpenList;
                tentative_is_better = true;
            }

            if (tentative_is_better)
            {
                y->parent = x;
                y->g_value = temp_g;
                y->f_value = y->g_value + y->h_value;
            }
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    loopIterations = closedList.size();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    while (!openList.empty())
    {
        delete openList.begin()->second;
        openList.erase(openList.begin());
    }

    for(auto & i : closedList)
        delete i;

    return pathToGoal;
}

void A_star_solver::reconstructPath(Node *node)
{
    if(node->parent != nullptr)
    {
        reconstructPath(node->parent);
    }
    node->isVisited = true;
    pathToGoal.push_back(node->n_puzzle_array);
}

A_star_solver::~A_star_solver()
{
    delete goal;
}

std::chrono::milliseconds A_star_solver::getDuration()
{
    return duration;
}

int A_star_solver::getLoopIterations()
{
    return loopIterations;
}
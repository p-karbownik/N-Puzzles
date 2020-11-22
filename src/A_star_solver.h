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
    class Node
    {
    public:
        std::vector<std::vector<int>> n_puzzle_array;
        bool isVisited;
        int f_value;
        int g_value;
        int h_value;

        int blank_field_row;
        int blank_field_column;
        Node* parent;

        Node();
        Node(std::vector<std::vector<int>> n_puzzle_array);
        Node(const Node &node);
        Node(int dimension);

        bool operator<(const Node& node) const;
        bool operator>(const Node& node) const;
        bool operator==(const Node& node) const;

        Node* getNeighbour(int direction);
    };

    Node* root;
    Node* goal;

    int calculateManhattanDistanceValue(Node* node);
    int calculateLinearConflictsValue(Node* node);
    int calculateHValue(Node* node);
    int dimension;
    std::vector<Node*> pathToGoal;
    Node* getFromOpenSet(Node* node, std::set<std::pair<int, Node*>>);
    void reconstructPath(Node* end);

public:
    A_star_solver(std::vector<std::vector<int>> root_array)
    {
        root = new Node(root_array);
        dimension = root_array.size();
        goal = new Node(dimension);
    };
    bool solve();
    void printSolution();
};


#endif //NPUZZLES_A_STAR_SOLVER_H

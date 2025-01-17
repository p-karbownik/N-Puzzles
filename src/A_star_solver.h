//
// Created by patryk on 10.11.2020.
//

#ifndef NPUZZLES_A_STAR_SOLVER_H
#define NPUZZLES_A_STAR_SOLVER_H

#include <vector>
#include <cstdlib>
#include <chrono>

class A_star_solver
{
private:
    class Node
    {
    private:
        int calculateManhattanDistanceValue();
        int calculateLinearConflictsValue();
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
        Node* getNeighbour(int direction);
        void setHValue();
    };

    Node* root;
    Node* goal;

    std::chrono::milliseconds duration;
    int loopIterations;

    std::vector<std::vector<std::vector<int>>> pathToGoal;

    Node* getFromOpenSet(Node* node, std::set<std::pair<int, Node*>>);
    bool isInClosedList(Node* node, std::vector<Node*> &closedSet);
    void reconstructPath(Node* end);

public:
    explicit A_star_solver(std::vector<std::vector<int>> root_array)
    {
        root = new Node(root_array);
        goal = new Node(root_array.size());
    };

    bool solve();
    ~A_star_solver();
    std::chrono::milliseconds getDuration();
    int getLoopIterations();
    std::vector<std::vector<std::vector<int>>> getPathToGoal();
};


#endif //NPUZZLES_A_STAR_SOLVER_H

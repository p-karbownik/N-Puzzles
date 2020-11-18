#include<iostream>
#include<vector>
#include<unordered_set>
#include<queue>

#include"BFS_solver.hpp"

BFS_solver::BFS_solver(vector<vector<int> > init) {
        root = new BFS_solver::Node(init);
        graph.insert(*root);
        puzzleSize = init.size();
        goal = vector<vector<int> > (puzzleSize, vector<int> (puzzleSize));
        int c = 1;
        for (int i = 0; i < puzzleSize; i++) {
            for (int j = 0; j < puzzleSize; j++) {
                goal.position[i][j] = c;
                c++;
            }
        }
        goal.position[puzzleSize - 1][puzzleSize - 1] = -1;
        goal.y_empty = puzzleSize - 1;
        goal.x_empty = puzzleSize - 1;
    }

vector<BFS_solver::Node*> BFS_solver::BFS(){
        queue<BFS_solver::Node*> toCheck;
        toCheck.push(root);
        while(!toCheck.empty()) {
            BFS_solver::Node* current = toCheck.front();
            toCheck.pop();
            if(*current == goal) {
                vector<BFS_solver::Node*> path;
                path.push_back(current);
                while(current->parent != nullptr) {
                    // cout << current->y_empty << ' ' << current->x_empty << "  ";
                    cout << ((current->lastMove == Direction::Up) ? "UP" : ((current->lastMove == Direction::Right) ? "RIGHT" : ((current->lastMove == Direction::Down) ? "DOWN" : "LEFT"))) << " ";
                    current = current->parent;
                    path.push_back(current);
                }
                return path;
            }
            if (current->y_empty < puzzleSize - 1) {
                BFS_solver::Node *nextUp = moveUp(current);
                if (!graph.count(*nextUp)) {
                    graph.insert(*nextUp);
                    toCheck.push(nextUp);
                }
            }
            if (current->y_empty > 0) {
                BFS_solver::Node *nextDown = moveDown(current);
                if (!graph.count(*nextDown)) {
                    graph.insert(*nextDown);
                    toCheck.push(nextDown);
                }
            }
            if (current->x_empty > 0) {
                BFS_solver::Node *nextRight = moveRight(current);
                if (!graph.count(*nextRight)) {
                    graph.insert(*nextRight);
                    toCheck.push(nextRight);
                }
            }
            if (current->x_empty < puzzleSize - 1) {
                BFS_solver::Node *nextLeft = moveLeft(current);
                if (!graph.count(*nextLeft)) {
                    graph.insert(*nextLeft);
                    toCheck.push(nextLeft);
                }
            }
        }
    }

    BFS_solver::Node* BFS_solver::moveUp(BFS_solver::Node *current) {
        return new Node(current, current->x_empty, current->y_empty + 1, Direction::Up);
    }
    BFS_solver::Node* BFS_solver::moveRight(BFS_solver::Node *current) {
        return new Node(current, current->x_empty - 1, current->y_empty, Direction::Right);
    }
    BFS_solver::Node* BFS_solver::moveDown(BFS_solver::Node *current) {
        return new Node(current, current->x_empty, current->y_empty - 1, Direction::Down);
    }
    BFS_solver::Node* BFS_solver::moveLeft(BFS_solver::Node *current) {
        return new Node(current, current->x_empty + 1, current->y_empty, Direction::Left);
    }
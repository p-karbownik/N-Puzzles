#include<iostream>
#include<vector>
#include<unordered_set>
#include<queue>

#include"BFS_solver.hpp"

using namespace std;

BFS_solver::BFS_solver(vector<vector<int> > init) {
    root = new Node(init);
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

vector<BFS_solver::Node> BFS_solver::BFS(){
    queue<Node*> toCheck;
    toCheck.push(root);
    while(!toCheck.empty()) {
        Node* current = toCheck.front();
        toCheck.pop();
        if(*current == goal) {
            vector<Node> path;
            path.push_back(*current);
            while(current->parent != nullptr) {
                cout << "(" << current->y_empty << ", " << current->x_empty << ") ";
                cout << ((current->lastMove == Direction::Up) ? "UP" : ((current->lastMove == Direction::Right) ? "RIGHT" : ((current->lastMove == Direction::Down) ? "DOWN" : "LEFT"))) << endl;
                current = current->parent;
                path.push_back(*current);
            }
            return path;
        }
        if (current->y_empty < puzzleSize - 1) {
            Node *nextUp = moveUp(current);
            if (!graph.count(*nextUp)) {
                graph.insert(*nextUp);
                toCheck.push(nextUp);
            }
        }
        if (current->y_empty > 0) {
            Node *nextDown = moveDown(current);
            if (!graph.count(*nextDown)) {
                graph.insert(*nextDown);
                toCheck.push(nextDown);
            }
        }
        if (current->x_empty > 0) {
            Node *nextRight = moveRight(current);
            if (!graph.count(*nextRight)) {
                graph.insert(*nextRight);
                toCheck.push(nextRight);
            }
        }
        if (current->x_empty < puzzleSize - 1) {
            Node *nextLeft = moveLeft(current);
            if (!graph.count(*nextLeft)) {
                graph.insert(*nextLeft);
                toCheck.push(nextLeft);
            }
        }
    }
}
BFS_solver::Node* BFS_solver::moveUp(Node *current) {
    return new Node(current, current->x_empty, current->y_empty + 1, Direction::Up);
}
BFS_solver::Node* BFS_solver::moveRight(Node *current) {
    return new Node(current, current->x_empty - 1, current->y_empty, Direction::Right);
}
BFS_solver::Node* BFS_solver::moveDown(Node *current) {
    return new Node(current, current->x_empty, current->y_empty - 1, Direction::Down);
}
BFS_solver::Node* BFS_solver::moveLeft(Node *current) {
    return new Node(current, current->x_empty + 1, current->y_empty, Direction::Left);
}

BFS_solver::Node::Node(Node *prev, int x, int y, Direction lm) {
    parent = prev;
    y_empty = y;
    x_empty = x;
    position = prev->position;
    int tile = position[y_empty][x_empty];
    position[prev->y_empty][prev->x_empty] = tile;
    position[y_empty][x_empty] = -1;
    lastMove = lm;
}
BFS_solver::Node::Node(vector<vector<int> > pos) {
    parent = nullptr;
    position = pos;
    lastMove = Direction::None;
    for (int i = 0; i < pos.size(); i++) {
        for (int j = 0; j < pos.size(); j++) {
            if (position[i][j] == -1) {
                y_empty = i;
                x_empty = j;
            }
        }
    }
}
bool BFS_solver::Node::operator==(const Node &that) const {
    for (int i = 0; i < this->position.size() && i < that.position.size(); i++) {
        for (int j = 0; j < this->position[i].size() && j < that.position[i].size(); j++) {
            if (this->position[i][j] != that.position[i][j]) return false;
        }
    }
    return true;
}
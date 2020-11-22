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
            goal.grid[i][j] = c;
            c++;
        }
    }
    goal.grid[puzzleSize - 1][puzzleSize - 1] = -1;
    goal.y_blank = puzzleSize - 1;
    goal.x_blank = puzzleSize - 1;
}

vector<BFS_solver::Node> BFS_solver::solve(){
    queue<Node*> toCheck;
    toCheck.push(root);
    while(!toCheck.empty()) {
        Node* current = toCheck.front();
        toCheck.pop();
        if(*current == goal) {
            vector<Node> path;
            path.push_back(*current);
            while(current->parent != nullptr) {
                cout << "(" << current->y_blank << ", " << current->x_blank << ") ";
                cout << ((current->last_move == Direction::Up) ? "UP" : 
                ((current->last_move == Direction::Right) ? "RIGHT" : 
                ((current->last_move == Direction::Down) ? "DOWN" : "LEFT"))) << endl;
                current = current->parent;
                path.push_back(*current);
            }
            return path;
        }
        if (current->y_blank < puzzleSize - 1) {
            Node *next_up = moveUp(current);
            if (!graph.count(*next_up)) {
                graph.insert(*next_up);
                toCheck.push(next_up);
            }
        }
        if (current->y_blank > 0) {
            Node *next_down = moveDown(current);
            if (!graph.count(*next_down)) {
                graph.insert(*next_down);
                toCheck.push(next_down);
            }
        }
        if (current->x_blank > 0) {
            Node *next_right = moveRight(current);
            if (!graph.count(*next_right)) {
                graph.insert(*next_right);
                toCheck.push(next_right);
            }
        }
        if (current->x_blank < puzzleSize - 1) {
            Node *next_left = moveLeft(current);
            if (!graph.count(*next_left)) {
                graph.insert(*next_left);
                toCheck.push(next_left);
            }
        }
    }
}
BFS_solver::Node* BFS_solver::moveUp(Node *current) {
    return new Node(current, current->x_blank, current->y_blank + 1, Direction::Up);
}
BFS_solver::Node* BFS_solver::moveRight(Node *current) {
    return new Node(current, current->x_blank - 1, current->y_blank, Direction::Right);
}
BFS_solver::Node* BFS_solver::moveDown(Node *current) {
    return new Node(current, current->x_blank, current->y_blank - 1, Direction::Down);
}
BFS_solver::Node* BFS_solver::moveLeft(Node *current) {
    return new Node(current, current->x_blank + 1, current->y_blank, Direction::Left);
}

BFS_solver::Node::Node(Node *prev, int x, int y, Direction lm) {
    parent = prev;
    y_blank = y;
    x_blank = x;
    grid = prev->grid;
    int tile = grid[y_blank][x_blank];
    grid[prev->y_blank][prev->x_blank] = tile;
    grid[y_blank][x_blank] = -1;
    last_move = lm;
}
BFS_solver::Node::Node(vector<vector<int> > pos) {
    parent = nullptr;
    grid = pos;
    last_move = Direction::None;
    for (int i = 0; i < pos.size(); i++) {
        for (int j = 0; j < pos.size(); j++) {
            if (grid[i][j] == -1) {
                y_blank = i;
                x_blank = j;
            }
        }
    }
}
bool BFS_solver::Node::operator==(const Node &that) const {
    for (int i = 0; i < this->grid.size() && i < that.grid.size(); i++) {
        for (int j = 0; j < this->grid[i].size() && j < that.grid[i].size(); j++) {
            if (this->grid[i][j] != that.grid[i][j]) return false;
        }
    }
    return true;
}

std::size_t BFS_solver::node_hash::operator()(const Node &N) const {
    boost::hash<std::vector<int> > vector_hash;
    std::vector<int> row_hashes;
    for (int i = 0; i < N.grid.size(); i++) {
        row_hashes.push_back(vector_hash(N.grid[i]));
    }
    return vector_hash(row_hashes);
}
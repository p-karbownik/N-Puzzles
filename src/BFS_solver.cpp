#include<iostream>
#include<vector>
#include<unordered_set>
#include<queue>

#include<boost/functional/hash.hpp>

#include"BFS_solver.hpp"
#include"Solvability_verifier.hpp"

using namespace std;

BFS_solver::BFS_solver(vector<vector<int> > init) {
    root = new Node(init);
    graph.insert(*root);
    puzzleSize = init.size();

    if (puzzleSize != 0) {
    goal = vector<vector<int> > (puzzleSize, vector<int> (puzzleSize));
        int c = 1;
        for (int i = 0; i < puzzleSize; i++) {
            for (int j = 0; j < puzzleSize; j++) {
                goal.grid[i][j] = c;
                c++;
            }
        }
        goal.grid[puzzleSize - 1][puzzleSize - 1] = blank_value;
        goal.y_blank = puzzleSize - 1;
        goal.x_blank = puzzleSize - 1;
    }
}

BFS_solver::~BFS_solver() {
    delete root;
}

bool BFS_solver::solve(){
    Solvability_verifier verifier;
    if (!verifier.solvable(root->grid, blank_value)) return false;

    queue<Node*> toCheck;
    toCheck.push(root);
    while(!toCheck.empty()) {
        Node* current = toCheck.front();
        toCheck.pop();

        if(*current == goal) {
            solution.push_back(current);
            while(current->parent != nullptr) {
                current = current->parent;
                solution.push_back(current);
            }
            return true;
        }

        if (current->y_blank < puzzleSize - 1) {
            Node *next_up = move_up(current);
            if (!graph.count(*next_up)) {
                graph.insert(*next_up);
                toCheck.push(next_up);
            }
        }
        if (current->y_blank > 0) {
            Node *next_down = move_down(current);
            if (!graph.count(*next_down)) {
                graph.insert(*next_down);
                toCheck.push(next_down);
            }
        }
        if (current->x_blank > 0) {
            Node *next_right = move_right(current);
            if (!graph.count(*next_right)) {
                graph.insert(*next_right);
                toCheck.push(next_right);
            }
        }
        if (current->x_blank < puzzleSize - 1) {
            Node *next_left = move_left(current);
            if (!graph.count(*next_left)) {
                graph.insert(*next_left);
                toCheck.push(next_left);
            }
        }
    }
}

vector<vector<vector<int> > > BFS_solver::get_solution() {
    vector<vector<vector<int> > > result;
    for (int i = solution.size() - 1; i >= 0; i--) {
        result.push_back(solution[i]->grid);
    }
}

BFS_solver::Node* BFS_solver::move_up(Node *current) {
    Node* temp = new Node(current, current->x_blank, current->y_blank + 1);
    current->children[0] = temp;
    return temp;
}
BFS_solver::Node* BFS_solver::move_right(Node *current) {
    Node* temp = new Node(current, current->x_blank - 1, current->y_blank);
    current->children[1] = temp;
    return temp;
}
BFS_solver::Node* BFS_solver::move_down(Node *current) {
    Node* temp = new Node(current, current->x_blank, current->y_blank - 1);
    current->children[2] = temp;
    return temp;
}
BFS_solver::Node* BFS_solver::move_left(Node *current) {
    Node* temp = new Node(current, current->x_blank + 1, current->y_blank);
    current->children[3] = temp;
    return temp;
}

BFS_solver::Node::Node(Node *prev, int x, int y) {
    parent = prev;
    for (int i = 0; i < 4; i++) {
        children[i] = nullptr;
    }
    y_blank = y;
    x_blank = x;
    grid = prev->grid;
    int tile = grid[y_blank][x_blank];
    grid[prev->y_blank][prev->x_blank] = tile;
    grid[y_blank][x_blank] = blank_value;
}

BFS_solver::Node::Node(vector<vector<int> > pos) {
    parent = nullptr;
    for (int i = 0; i < 4; i++) {
        children[i] = nullptr;
    }
    grid = pos;
    for (int i = 0; i < pos.size(); i++) {
        for (int j = 0; j < pos.size(); j++) {
            if (grid[i][j] == blank_value) {
                y_blank = i;
                x_blank = j;
            }
        }
    }
}

BFS_solver::Node::~Node() {
    for (int i = 0; i < 4; i++) {
        if (children[i] != nullptr) 
            delete children[i];
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

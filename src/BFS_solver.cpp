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

bool BFS_solver::solve(){
    if (!is_solvable(root->grid)) return false;
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


void BFS_solver::print_solution() {
    int size = solution.size();
    for (int i = size - 2; i >= 0; i--) {
        cout << size - i - 1 << ": ";
        cout << "(" << solution[i]->y_blank << ", " << solution[i]->x_blank << ") ";
        cout << ((solution[i]->last_move == Direction::Up) ? "UP" : 
            ((solution[i]->last_move == Direction::Right) ? "RIGHT" : 
            ((solution[i]->last_move == Direction::Down) ? "DOWN" : "LEFT"))) << endl;
    }
}

BFS_solver::Node* BFS_solver::move_up(Node *current) {
    return new Node(current, current->x_blank, current->y_blank + 1, Direction::Up);
}
BFS_solver::Node* BFS_solver::move_right(Node *current) {
    return new Node(current, current->x_blank - 1, current->y_blank, Direction::Right);
}
BFS_solver::Node* BFS_solver::move_down(Node *current) {
    return new Node(current, current->x_blank, current->y_blank - 1, Direction::Down);
}
BFS_solver::Node* BFS_solver::move_left(Node *current) {
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


bool BFS_solver::is_solvable(std::vector<std::vector<int> > &V) {
    int row_length = V.size();
    int grid_length = row_length * row_length;
    bool grid_length_odd = grid_length & 1;

    int blank_row;             //from bottom
    vector<int> linear;
    for (int i = 0; i < row_length; i++) {
        for (int j = 0; j < row_length; j++) {
            linear.push_back(V[i][j]);
            if (V[i][j] == -1) {
                blank_row = row_length - i;
            }
        }
    }
    bool blank_on_odd = blank_row & 1;

    int inversions = 0;
    for (int i = 0; i < grid_length - 1; i++) {
        if (linear[i] == -1) continue;
        for (int j = i + 1; j < grid_length; j++) {
            if (linear[i] > linear[j] && linear[j] != -1) 
                inversions++;
        }
    }
    bool inversions_odd = inversions & 1;

    return ((grid_length_odd) && !inversions_odd) || (!grid_length_odd && (blank_on_odd == !inversions_odd));
}
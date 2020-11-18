#ifndef NPUZZLES_BFS_SOLVER
#define NPUZZLES_BFS_SOLVER

#include<iostream>
#include<vector>
#include<unordered_set>
#include<queue>

using namespace std;

class BFS_solver {
    enum class Direction {Up, Right, Down, Left, None};
    class Node {
    public:
        Node *parent;
        int y_empty, x_empty;
        vector<vector<int> > position;
        Direction lastMove;
        Node() {}
        Node(vector<vector<int> > pos) {
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
        Node(Node *prev, int x, int y, Direction lm) {
            parent = prev;
            y_empty = y;
            x_empty = x;
            position = prev->position;
            int tile = position[y_empty][x_empty];
            position[prev->y_empty][prev->x_empty] = tile;
            position[y_empty][x_empty] = -1;
            lastMove = lm;
        }
        bool operator==(const Node &that) const {
            for (int i = 0; i < this->position.size() && i < that.position.size(); i++) {
                for (int j = 0; j < this->position[i].size() && j < that.position[i].size(); j++) {
                    if (this->position[i][j] != that.position[i][j]) return false;
                }
            }
            return true;
        }
    };
    struct myHash {         //TODO: add a proper hash function
        std::size_t operator()(const Node &V) const {
            return V.position[1][1];
        }
    };
    Node *root;
    unordered_set<Node, myHash> graph;
    Node goal;
    int puzzleSize;

public:
    BFS_solver(vector<vector<int> > init);

    Node* moveUp(Node *current);
    Node* moveRight(Node *current);
    Node* moveDown(Node *current);
    Node* moveLeft(Node *current);

    vector<Node*> BFS();
};

#endif //NPUZZLES_BFS_SOLVER
#ifndef NPUZZLES_BFS_SOLVER
#define NPUZZLES_BFS_SOLVER

#include<vector>
#include<unordered_set>


class BFS_solver {
    enum class Direction {Up, Right, Down, Left, None};
    class Node {
    public:
        Node *parent;
        int y_empty, x_empty;
        std::vector<std::vector<int> > position;
        Direction lastMove;
        Node() {}
        Node(std::vector<std::vector<int> > pos);
        Node(Node *prev, int x, int y, Direction lm);
        bool operator==(const Node &that) const;
    };
    struct myHash {         //TODO: add a proper hash function
        std::size_t operator()(const Node &V) const {
            return V.position[1][1];
        }
    };
    Node *root;
    std::unordered_set<Node, myHash> graph;
    Node goal;
    int puzzleSize;

public:
    BFS_solver(std::vector<std::vector<int> > init);

    Node* moveUp(Node *current);
    Node* moveRight(Node *current);
    Node* moveDown(Node *current);
    Node* moveLeft(Node *current);

    std::vector<Node*> BFS();
};

#endif //NPUZZLES_BFS_SOLVER
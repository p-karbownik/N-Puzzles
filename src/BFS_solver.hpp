#ifndef NPUZZLES_BFS_SOLVER
#define NPUZZLES_BFS_SOLVER

#include<vector>
#include<unordered_set>
#include <boost/functional/hash.hpp>


class BFS_solver {
    enum class Direction {Up, Right, Down, Left, None};

    struct Node {
        Node *parent;
        int y_empty, x_empty;
        std::vector<std::vector<int> > position;
        Direction lastMove;

        Node() {}
        Node(std::vector<std::vector<int> > pos);
        Node(Node *prev, int x, int y, Direction lm);
        bool operator==(const Node &that) const;
    };
    struct myHash {
        std::size_t operator()(const Node &N) const {
            boost::hash<std::vector<int> > vectorHash;
            std::vector<int> rowHashes;
            for (int i = 0; i < N.position.size(); i++) {
                rowHashes.push_back(vectorHash(N.position[i]));
            }
            return vectorHash(rowHashes);
        }
    };

    Node *root;
    std::unordered_set<Node, myHash> graph;
    Node goal;
    int puzzleSize;

public:
    BFS_solver(std::vector<std::vector<int> > init);

    std::vector<Node> BFS();

    Node* moveUp(Node *current);
    Node* moveRight(Node *current);
    Node* moveDown(Node *current);
    Node* moveLeft(Node *current);
};

#endif //NPUZZLES_BFS_SOLVER
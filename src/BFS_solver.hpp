#ifndef NPUZZLES_BFS_SOLVER
#define NPUZZLES_BFS_SOLVER

#include<vector>
#include<unordered_set>
#include<boost/functional/hash.hpp>


class BFS_solver {
    enum class Direction {Up, Right, Down, Left, None};

    struct Node {
        Node *parent;
        int y_blank, x_blank;
        std::vector<std::vector<int> > grid;
        Direction last_move;

        Node() {}
        Node(std::vector<std::vector<int> > pos);
        Node(Node *prev, int x, int y, Direction lm);
        bool operator==(const Node &that) const;
    };
    struct node_hash {
        std::size_t operator()(const Node &N) const;
    };

    Node *root;
    std::unordered_set<Node, node_hash> graph;
    Node goal;
    int puzzleSize;
    std::vector<Node*> solution;

    bool is_solvable(std::vector<std::vector<int> > &V);

    Node* move_up(Node *current);
    Node* move_right(Node *current);
    Node* move_down(Node *current);
    Node* move_left(Node *current);
public:
    BFS_solver(std::vector<std::vector<int> > init);

    bool solve();
    void print_solution();
};

#endif //NPUZZLES_BFS_SOLVER
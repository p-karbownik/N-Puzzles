#ifndef NPUZZLES_BFS_SOLVER
#define NPUZZLES_BFS_SOLVER

#include<vector>
#include<unordered_set>
#include<chrono>


class BFS_solver {

    struct Node {
        Node *parent;
        int y_blank, x_blank;
        Node* children[4];
        std::vector<std::vector<int> > grid;

        Node() {}
        Node(std::vector<std::vector<int> > pos);
        Node(Node *prev, int x, int y);

        ~Node();

        bool operator==(const Node &that) const;
    };
    struct node_hash {
        std::size_t operator()(const Node &N) const;
    };

    int puzzleSize;
    const static int blank_value = -1;

    Node *root;
    std::unordered_set<Node, node_hash> graph;

    Node goal;
    std::vector<Node*> solution;

    int loop_iterations;
    std::chrono::milliseconds duration;

    Node* move_up(Node *current);
    Node* move_right(Node *current);
    Node* move_down(Node *current);
    Node* move_left(Node *current);
public:
    BFS_solver(std::vector<std::vector<int> > init);
    ~BFS_solver();

    bool solve();
    std::vector<std::vector<std::vector<int> > > get_solution();

    std::chrono::milliseconds getDuration();
    int getLoopIterations();
};

#endif //NPUZZLES_BFS_SOLVER
#ifndef NPUZZLES_BFS_SOLVER
#define NPUZZLES_BFS_SOLVER

#include<vector>
#include<queue>
#include<unordered_set>
#include<boost/functional/hash.hpp>


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

    Node *root;
    std::unordered_set<Node, node_hash> graph;
    std::queue<Node*> toCheck;
    Node goal;
    int puzzleSize;
    const static int blank_value = -1;
    std::vector<Node*> solution;

    void clear(std::queue<Node*> &Q);

    Node* move_up(Node *current);
    Node* move_right(Node *current);
    Node* move_down(Node *current);
    Node* move_left(Node *current);
public:
    BFS_solver(std::vector<std::vector<int> > init);
    ~BFS_solver();

    bool solve();
    std::vector<std::vector<std::vector<int> > > get_solution();
};

#endif //NPUZZLES_BFS_SOLVER
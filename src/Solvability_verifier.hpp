#ifndef NPUZZLES_SOLVABILITY_VERIFIER
#define NPUZZLES_SOLVABILITY_VERIFIER

#include<vector>

class Solvability_verifier {
public:
    bool solvable(std::vector<std::vector<int> > &grid, int blank_value);
};

#endif //NPUZZLES_SOLVABILITY_VERIFIER
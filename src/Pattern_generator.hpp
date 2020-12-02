#ifndef NPUZZLES_PATTERN_GENERATOR
#define NPUZZLES_PATTERN_GENERATOR

#include<vector>

class Pattern_generator {
private:
    void shuffle(std::vector<std::vector<int> > &grid, int N, int width);
public:
    bool generate(std::vector<std::vector<int> > &grid, int N);
};

#endif //NPUZZLES_PATTERN_GENERATOR
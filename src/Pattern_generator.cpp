// #include<vector>
#include<random>
#include<algorithm>

#include"Pattern_generator.hpp"
#include"Solvability_verifier.hpp"

using namespace std;

void Pattern_generator::generate(vector<vector<int> > &grid, int N) {
    int blank_value = -1;
    Solvability_verifier verifier;
    int width = sqrt(N + 1);
    do {
        grid.clear();
        shuffle(grid, N, width);
    } while (!verifier.solvable(grid, blank_value));
}

void Pattern_generator::shuffle(std::vector<std::vector<int> > &grid, int N, int width) {
    vector<int> buffer(N + 1);
    for(int i = 0; i < N; i++) {
        buffer[i] = i + 1;
    }
    buffer[N] = -1;

    random_device engine;

    int buffer_size = N + 1;

    for (int i = 0; i < width; i++) {
        vector<int> temp;
        grid.push_back(temp);

        for (int j = 0; j < width; j++) {
            uniform_int_distribution<int> distribution(0, buffer_size - 1);
            int index = distribution(engine);
            grid[i].push_back(buffer[index]);

            swap(buffer[index], buffer[buffer_size - 1]);
            buffer.pop_back();

            buffer_size--;
        }
    }
}
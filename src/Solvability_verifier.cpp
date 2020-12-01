#include "Solvability_verifier.hpp"

using namespace std;

bool Solvability_verifier::solvable(vector<vector<int> > &grid, int blank_value) {
    int row_length = grid.size();
    int grid_length = row_length * row_length;
    bool grid_length_odd = grid_length & 1;

    int blank_row;             //from bottom
    vector<int> linear;
    for (int i = 0; i < row_length; i++) {
        for (int j = 0; j < row_length; j++) {
            linear.push_back(grid[i][j]);
            if (grid[i][j] == blank_value) {
                blank_row = row_length - i;
            }
        }
    }
    bool blank_on_odd = blank_row & 1;

    int inversions = 0;
    for (int i = 0; i < grid_length - 1; i++) {
        if (linear[i] == blank_value) continue;
        for (int j = i + 1; j < grid_length; j++) {
            if (linear[i] > linear[j] && linear[j] != blank_value) 
                inversions++;
        }
    }
    bool inversions_odd = inversions & 1;

    return ((grid_length_odd) && !inversions_odd) || (!grid_length_odd && (blank_on_odd == !inversions_odd));
}
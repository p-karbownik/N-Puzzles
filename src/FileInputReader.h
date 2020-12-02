//
// Created by patryk on 01.12.2020.
//

#ifndef NPUZZLES_FILEINPUTREADER_H
#define NPUZZLES_FILEINPUTREADER_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
class FileInputReader
{
private:
    std::string fileName;
    std::vector<std::vector<std::vector<int>>> puzzles;
    bool displayPath;
    int whichSolver;
    int puzzlesAmount;
    int currentPuzzleNumber;
public:
    FileInputReader(std::string s);
    std::vector<std::vector<int>> getPuzzleToSolve();
    void read();
    void setNextPuzzle();
    void setPreviousPuzzle();
    int getWhichSolver();
    int getPuzzlesAmount();
    bool getDisplayPath();
};


#endif //NPUZZLES_FILEINPUTREADER_H

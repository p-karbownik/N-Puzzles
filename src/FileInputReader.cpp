//
// Created by patryk on 01.12.2020.
//

#include "FileInputReader.h"
FileInputReader::FileInputReader(std::string s)
{
    fileName = s;
    displayPath = false;
    whichSolver = 0;
    puzzlesAmount = 0;
    currentPuzzleNumber = 0;
}

std::vector<std::vector<int>> FileInputReader::getPuzzleToSolve()
{
    return puzzles.at(currentPuzzleNumber);
}

void FileInputReader::read()
{
    std::fstream file(fileName, std::ios_base::in);
    int temp;

    file >> puzzlesAmount;
    file >> whichSolver;
    file >> temp;
    std::cout << puzzlesAmount << whichSolver << temp;
    if(temp == 1)
        displayPath = true;

    for(int i = 0; i < puzzlesAmount; i++)
    {
        int dimension;
        file >> dimension;
        std::cout << dimension;
        std::vector<std::vector<int>> aVector;
        for(int j = 0; j < dimension; j++)
        {
            std::vector<int> innerVector;
            for (int k = 0; k < dimension; k++)
            {
                file >> temp;
                std::cout << temp;
                innerVector.push_back(temp);
            }
            aVector.push_back(innerVector);
        }
        puzzles.push_back(aVector);
    }
}

void FileInputReader::setNextPuzzle()
{
    if (currentPuzzleNumber < puzzlesAmount - 1)
        currentPuzzleNumber++;
}

void FileInputReader::setPreviousPuzzle()
{
    if (currentPuzzleNumber >= 1)
        currentPuzzleNumber--;
}

int FileInputReader::getPuzzlesAmount()
{
    return puzzlesAmount;
}

int FileInputReader::getWhichSolver()
{
    return whichSolver;
}

bool FileInputReader::getDisplayPath()
{
    return displayPath;
}
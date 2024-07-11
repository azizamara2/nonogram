#include "NonogramPattern.h"
#include <vector>
#include <cstdlib>

std::vector<std::vector<char>> NonogramPattern::generateRandomPattern(int size, const std::string &difficulty)
{
    double fillPercentage;
    if (difficulty == "easy")
    {
        fillPercentage = 0.9;
    }
    else if (difficulty == "medium")
    {
        fillPercentage = 0.6;
    }
    else if (difficulty == "hard")
    {
        fillPercentage = 0.4;
    }
    std::vector<std::vector<char>> pattern(size, std::vector<char>(size, ' '));
    int filledBoxes = static_cast<int>(size * size * fillPercentage);
    for (int i = 0; i < filledBoxes; ++i)
    {
        int x = rand() % size;
        int y = rand() % size;
        pattern[x][y] = '#';
    }
    return pattern;
}
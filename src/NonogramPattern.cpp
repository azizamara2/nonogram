#include "NonogramPattern.h"
#include <vector>
#include <cstdlib>

std::vector<std::vector<char>> NonogramPattern::generateRandomPattern(int size, const std::string &difficulty)
{
    std::vector<std::vector<char>> pattern(size, std::vector<char>(size, ' '));
    int filledBoxes = size * size * 0.9; // Adjusted difficulty to fill more boxes

    for (int i = 0; i < filledBoxes; ++i)
    {
        int x = rand() % size;
        int y = rand() % size;
        pattern[x][y] = '#';
    }
    return pattern;
}
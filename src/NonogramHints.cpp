#include "NonogramHints.h"
#include <vector>

std::vector<std::vector<int>> NonogramHints::calculateHints(const std::vector<std::vector<char>> &pattern, bool rows)
{
    int size = pattern.size();
    std::vector<std::vector<int>> hints(size, std::vector<int>());

    if (rows)
    {
        for (int i = 0; i < size; ++i)
        {
            hints[i] = generateHints(pattern[i]);
        }
    }
    else
    {
        for (int j = 0; j < size; ++j)
        {
            std::vector<char> column(size);
            for (int i = 0; i < size; ++i)
            {
                column[i] = pattern[i][j];
            }
            hints[j] = generateHints(column);
        }
    }
    return hints;
}

std::vector<int> NonogramHints::generateHints(const std::vector<char> &line)
{
    std::vector<int> hints;
    int count = 0;
    for (char cell : line)
    {
        if (cell == '#')
        {
            ++count;
        }
        else
        {
            if (count > 0)
            {
                hints.push_back(count);
                count = 0;
            }
        }
    }
    if (count > 0)
    {
        hints.push_back(count);
    }
    return hints;
}

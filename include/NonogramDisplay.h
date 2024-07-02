#ifndef NONOGRAMDISPLAY_H
#define NONOGRAMDISPLAY_H

#include <vector>

class NonogramDisplay
{
public:
    static void displayField(const std::vector<std::vector<char>> &field, const std::vector<std::vector<int>> &rowHints, const std::vector<std::vector<int>> &colHints);
};

#endif // NONOGRAMDISPLAY_H

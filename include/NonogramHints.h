#ifndef NONOGRAMHINTS_H
#define NONOGRAMHINTS_H

#include <vector>

class NonogramHints
{
public:
    static std::vector<std::vector<int>> calculateHints(const std::vector<std::vector<char>> &pattern, bool rows);

private:
    static std::vector<int> generateHints(const std::vector<char> &line);
};

#endif // NONOGRAMHINTS_H
#ifndef NONOGRAMPATTERN_H
#define NONOGRAMPATTERN_H

#include <vector>
#include <string>

class NonogramPattern
{
public:
    static std::vector<std::vector<char>> generateRandomPattern(int size, const std::string &difficulty);
};

#endif // NONOGRAMPATTERN_H
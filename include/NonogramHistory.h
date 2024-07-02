#ifndef NONOGRAMHISTORY_H
#define NONOGRAMHISTORY_H

#include <vector>
#include <string>

class NonogramHistory
{
public:
    static void saveGameHistory(const std::string &playerName, const std::vector<std::vector<char>> &field);
    static void updateHighScore(const std::string &playerName);
    static void displayHighScore();
};

#endif // NONOGRAMHISTORY_H

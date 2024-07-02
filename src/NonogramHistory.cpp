#include "NonogramHistory.h"
#include <fstream>
#include <iostream>

void NonogramHistory::saveGameHistory(const std::string &playerName, const std::vector<std::vector<char>> &field)
{
    std::ofstream file("game_history.txt", std::ios::app);
    file << "Player: " << playerName << std::endl;
    for (const auto &row : field)
    {
        for (char cell : row)
        {
            file << cell << " ";
        }
        file << std::endl;
    }
    file << std::endl;
    file.close();
}

void NonogramHistory::updateHighScore(const std::string &playerName)
{
    std::ofstream file("highscores.txt", std::ios::app);
    file << playerName << std::endl;
    file.close();
}

void NonogramHistory::displayHighScore()
{
    std::ifstream file("highscores.txt");
    std::string line;
    while (getline(file, line))
    {
        std::cout << line << std::endl;
    }
    file.close();
}

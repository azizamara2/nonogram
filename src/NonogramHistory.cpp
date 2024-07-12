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
    std::string fileName = "highscores.txt";

    // Ensure the file exists by creating it if it does not
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::ofstream createFile(fileName);
        if (!createFile) {
            std::cerr << "Error creating file: " << fileName << std::endl;
            return;
        }
        createFile.close();
    }
    inputFile.close();

    // Reopen the file for reading
    inputFile.open(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    std::map<std::string, int> highScores;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string name;
        int score;
        if (!(iss >> name >> score)) { 
            std::cerr << "Error reading line: " << line << std::endl;
            continue; 
        }
        highScores[name] = score;
    }
    inputFile.close();

    if (highScores.find(playerName) == highScores.end()) {
        highScores[playerName] = 0;
    }
    highScores[playerName] += 1;

    std::ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << fileName << std::endl;
        return;
    }

    for (const auto& pair : highScores) {
        outputFile << pair.first << " " << pair.second << std::endl;
    }
    outputFile.close();
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

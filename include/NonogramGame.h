#ifndef NONOGRAMGAME_H
#define NONOGRAMGAME_H

#include <vector>
#include <string>

class NonogramGame
{
public:
    NonogramGame(int size, bool isTest);
    void playGame();
    void playGameComputer();
    void displayMenu();
    void displayRules();
    void displayHighScore();

private:
    int size;
    int mistakes;
    int maxMistakes;
    std::string playerName;
    std::vector<std::vector<char>> field;
    std::vector<std::vector<char>> pattern;
    std::vector<std::vector<int>> rowHints;
    std::vector<std::vector<int>> colHints;
    bool markPattern;
    bool gameWon;

    void displayField();
    void saveGameHistory();
    void updateHighScore();
};

#endif // NONOGRAMGAME_H
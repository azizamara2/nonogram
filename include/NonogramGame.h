#ifndef NONOGRAMGAME_H
#define NONOGRAMGAME_H

#include <string>
#include <vector>

class NonogramGame
{
public:
    NonogramGame(int size, bool isTest, const std::string &language, const std::string &difficulty);

    void displayMenu();
    void displayRules();
    void playGame();
    void playGameComputer();
    void displayHighScore();
    void gameSettings();

private:
    int size;
    int mistakes = 0;
    const int maxMistakes = 3;
    bool markPattern;
    bool gameWon;
    std::string language;
    std::string difficulty = "easy";
    std::string playerName;
    std::vector<std::vector<char>> field;
    std::vector<std::vector<char>> playfield;
    std::vector<std::vector<char>> pattern;
    std::vector<std::vector<int>> rowHints;
    std::vector<std::vector<int>> colHints;

    void saveGameHistory();
    void updateHighScore();
};

#endif // NONOGRAMGAME_H

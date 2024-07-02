#include "NonogramGame.h"
#include "NonogramPattern.h"
#include "NonogramHints.h"
#include "NonogramDisplay.h"
#include "NonogramHistory.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <limits>
using namespace std;

NonogramGame::NonogramGame(int size, bool isTest)
    : size(isTest ? 5 : size), mistakes(0), maxMistakes(3), markPattern(true), gameWon(false)
{
    field = vector<vector<char>>(this->size, vector<char>(this->size, ' '));
    pattern = NonogramPattern::generateRandomPattern(this->size, "easy");
    rowHints = NonogramHints::calculateHints(pattern, true);
    colHints = NonogramHints::calculateHints(pattern, false);
}

void NonogramGame::displayMenu()
{
    int choice;
    do
    {
        cout << "----- Nonogram Menu -----" << endl;
        cout << "1. Play Game" << endl;
        cout << "2. Play Test Game (5x5)" << endl;
        cout << "3. Play Computer Game" << endl;
        cout << "4. Display High Score" << endl;
        cout << "5. Display Rules" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            playGame();
            break;
        case 2:
        {
            NonogramGame testGame(5, true);
            testGame.playGame();
            break;
        }
        case 3:
            playGameComputer();
            break;
        case 4:
            NonogramHistory::displayHighScore();
            break;
        case 5:
            displayRules();
            break;
        case 6:
            cout << "Exiting game. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}

void NonogramGame::displayRules()
{
    cout << "----- Nonogram Rules -----" << endl;
    cout << "1. The game is played on a grid where the goal is to reveal a hidden pattern." << endl;
    cout << "2. Numbers on the rows and columns indicate how many consecutive boxes are filled in." << endl;
    cout << "3. There can be multiple groups of filled boxes separated by empty boxes." << endl;
    cout << "4. The game ends when you make 3 mistakes or complete the pattern." << endl;
    cout << "5. You can switch between marking filled and empty boxes at any time." << endl;
    cout << "6. At the end of the game, the hidden pattern will be revealed." << endl;
}

void NonogramGame::playGame()
{
    cout << "Enter your name: ";
    cin >> playerName;

    while (mistakes < maxMistakes && !gameWon)
    {
        NonogramDisplay::displayField(field, rowHints, colHints);
        cout << "Marking mode: " << (markPattern ? "Pattern" : "Blank") << endl;
        cout << "Enter coordinates (row col) to mark, or 'toggle' to switch mode: ";
        string input;
        cin >> input;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter valid coordinates or 'toggle'." << endl;
            continue;
        }

        if (input == "toggle")
        {
            markPattern = !markPattern;
            continue;
        }

        int row;
        int col;

        try
        {
            row = stoi(input);
            cin >> input;
            col = stoi(input);
        }
        catch (invalid_argument &e)
        {
            cout << "Invalid coordinates. Please enter numbers for row and column." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        catch (out_of_range &e)
        {
            cout << "Coordinates out of range. Please enter valid row and column numbers." << endl;
            continue;
        }

        if (row < 0 || row >= size || col < 0 || col >= size)
        {
            cout << "Invalid coordinates. Try again." << endl;
            continue;
        }

        if (markPattern)
        {
            if (pattern[row][col] == '#')
            {
                field[row][col] = '#';
            }
            else
            {
                field[row][col] = 'X';
                ++mistakes;
                cout << "Mistake " << mistakes << "/" << maxMistakes << endl;
            }
        }
        else
        {
            if (pattern[row][col] == ' ')
            {
                field[row][col] = ' ';
            }
            else
            {
                field[row][col] = 'X';
                ++mistakes;
                cout << "Mistake " << mistakes << "/" << maxMistakes << endl;
            }
        }

        gameWon = (field == pattern);
    }

    if (gameWon)
    {
        cout << "Congratulations, you solved the Nonogram!" << endl;
    }
    else
    {
        cout << "Game over. You've made too many mistakes." << endl;
    }

    saveGameHistory();
    updateHighScore();
}

void NonogramGame::playGameComputer()
{
    while (mistakes < maxMistakes && !gameWon)
    {
        NonogramDisplay::displayField(field, rowHints, colHints);
        cout << "Computer is solving..." << endl;

        int row = rand() % size;
        int col = rand() % size;

        if (pattern[row][col] == '#')
        {
            field[row][col] = '#';
        }
        else
        {
            field[row][col] = 'X';
            ++mistakes;
            cout << "Computer made a mistake " << mistakes << "/" << maxMistakes << endl;
        }

        gameWon = (field == pattern);
    }

    if (gameWon)
    {
        cout << "Computer solved the Nonogram!" << endl;
    }
    else
    {
        cout << "Computer failed to solve the Nonogram." << endl;
    }

    saveGameHistory();
    updateHighScore();
}

void NonogramGame::saveGameHistory()
{
    NonogramHistory::saveGameHistory(playerName, field);
}

void NonogramGame::updateHighScore()
{
    NonogramHistory::updateHighScore(playerName);
}

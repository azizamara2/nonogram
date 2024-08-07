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

NonogramGame::NonogramGame(int size, bool isTest, const std::string &language,const std::string &difficulty)
    : size(isTest ? 5 : size), mistakes(0), maxMistakes(3), markPattern(true), gameWon(false), language(language), difficulty(difficulty)
{
    field = vector<vector<char>>(this->size, vector<char>(this->size, ' '));
    playfield = vector<vector<char>>(this->size, vector<char>(this->size, ' '));
    pattern = NonogramPattern::generateRandomPattern(this->size, difficulty);
    rowHints = NonogramHints::calculateHints(pattern, true);
    colHints = NonogramHints::calculateHints(pattern, false);
}

void NonogramGame::displayMenu()
{
    int choice;
    do
    {
        cout << "----- Nonogram Menu -----" << endl;
        cout << "1. " << (language == "deutsch" ? "Spiel starten" : "Play Game") << endl;
        cout << "2. " << (language == "deutsch" ? "Testspiel starten (5x5)" : "Play Test Game (5x5)") << endl;
        cout << "3. " << (language == "deutsch" ? "Computerspiel starten" : "Play Computer Game") << endl;
        cout << "4. " << (language == "deutsch" ? "Bestenliste anzeigen" : "Display High Score") << endl;
        cout << "5. " << (language == "deutsch" ? "Regeln anzeigen" : "Display Rules") << endl;
        cout << "6. " << (language == "deutsch" ? "Spieleinstellungen" : "Settings") << endl;
        cout << "7. " << (language == "deutsch" ? "Beenden" : "Exit") << endl;
        cout << (language == "deutsch" ? "Ihre Auswahl:" : "Enter your choice: ");
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << (language == "deutsch" ? "Ungültige Eingabe. Bitte geben Sie eine Zahl zwischen 1 und 7 ein." : "Invalid input. Please enter a number between 1 and 7.") << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            playGame();
            break;
        case 2:
        {
            NonogramGame testGame(5, true, language,difficulty);
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
            gameSettings();
            break;
        case 7:
            cout << (language == "deutsch" ? "Spiel wird beendet. Auf Wiedersehen!" : "Exiting game. Goodbye!") << endl;
            break;
        default:
            cout << (language == "deutsch" ? "Ungültige Auswahl. Bitte versuchen Sie es erneut." : "Invalid choice. Please try again.") << endl;
        }
    } while (choice != 7);
}

void NonogramGame::displayRules()
{
    cout << "----- Nonogram " << (language == "deutsch" ? "Regeln" : "Rules") << " -----" << endl;
    cout << "1. " << (language == "deutsch" ? "Das Spiel wird auf einem Gitter gespielt, Ziel ist es, ein verstecktes Muster zu enthüllen." : "The game is played on a grid where the goal is to reveal a hidden pattern.") << endl;
    cout << "2. " << (language == "deutsch" ? "Zahlen in den Zeilen und Spalten zeigen an, wie viele aufeinanderfolgende Kästchen gefüllt sind." : "Numbers on the rows and columns indicate how many consecutive boxes are filled in.") << endl;
    cout << "3. " << (language == "deutsch" ? "Es können mehrere Gruppen von gefüllten Kästchen durch leere Kästchen getrennt sein." : "There can be multiple groups of filled boxes separated by empty boxes.") << endl;
    cout << "4. " << (language == "deutsch" ? "Das Spiel endet, wenn Sie 3 Fehler gemacht haben oder das Muster vervollständigt haben." : "The game ends when you make 3 mistakes or complete the pattern.") << endl;
    cout << "5. " << (language == "deutsch" ? "Sie können jederzeit zwischen dem Markieren von gefüllten und leeren Kästchen wechseln." : "You can switch between marking filled and empty boxes at any time.") << endl;
    cout << "6. " << (language == "deutsch" ? "Am Ende des Spiels wird das versteckte Muster enthüllt." : "At the end of the game, the hidden pattern will be revealed.") << endl;
}

void NonogramGame::playGame()
{
    cout << (language == "deutsch" ? "Geben Sie Ihren Namen ein: " : "Enter your name: ");
    cin >> playerName;
    mistakes = 0;
    while (mistakes < maxMistakes && !gameWon)
    {
        NonogramDisplay::displayField(field, rowHints, colHints);
        cout << (language == "deutsch" ? "Markierungsmodus: " : "Marking mode: ") << (markPattern ? "Muster" : "Leere-Stellen-Markieren") << endl;
        cout << (language == "deutsch" ? "Geben Sie Koordinaten (Zeile Spalte) zum Markieren ein: " : "Enter coordinates (row col) to mark or 'toggle' to switch mode: ");
        string input;
        cin >> input;

        if (input == "toggle")
        {
            markPattern = !markPattern;
            continue;
        }

        int row,col;
        
        try
        {
            row = stoi(input);
            cin >> input;
            col = stoi(input);
        }

        catch (invalid_argument &e)
        {
            cout << (language == "deutsch" ? "Ungültige Koordinaten. Bitte geben Sie gültige Zahlen für Zeile und Spalte ein." : "Invalid coordinates. Please enter valid row and column numbers or 'toggle'.") << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        catch (out_of_range &e)
        {
            cout << (language == "deutsch" ? "Ungültige Koordinaten. Bitte geben Sie gültige Zahlen für Zeile und Spalte ein." : "Invalid coordinates. Please enter valid row and column numbers or 'toggle'.") << endl;
            continue;
        }

        if (row < 0 || row >= size || col < 0 || col >= size)
        {
            cout << (language == "deutsch" ? "Ungültige Koordinaten. Bitte geben Sie gültige Zahlen für Zeile und Spalte ein." : "Invalid coordinates. Please enter valid row and column numbers or 'toggle'.") << endl;
            continue;
        }

        if (markPattern)
        {
            if (pattern[row][col] == '#')
            {
                field[row][col] = '#';
                playfield[row][col] = '#';
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
                playfield[row][col] = ' ';
            }
            else
            {
                field[row][col] = 'X';
                ++mistakes;
                cout << "Mistake " << mistakes << "/" << maxMistakes << endl;
            }
        }
        gameWon = (playfield == pattern);
    }

    if (gameWon)
    {
        cout << (language == "deutsch" ? "Herzlichen Glückwunsch, Sie haben das Nonogram gelöst!" : "Congratulations, you solved the Nonogram!") << endl;
    }
    else
    {
        cout << (language == "deutsch" ? "Spiel vorbei. Sie haben zu viele Fehler gemacht." : "Game over. You've made too many mistakes.") << endl;
    }
    NonogramDisplay::displayField(pattern, rowHints, colHints);
    saveGameHistory();
    updateHighScore();
}

void NonogramGame::playGameComputer()
{
    while (mistakes < maxMistakes && !gameWon)
    {
        NonogramDisplay::displayField(field, rowHints, colHints);

        // Computer logic to play the game automatically can be added here
        // For demonstration purposes, we'll simulate random moves
        int row = rand() % size;
        int col = rand() % size;

        if (pattern[row][col] == '#')
        {
            field[row][col] = '#';
            playfield[row][col] = '#';
        }
        else
        {
            field[row][col] = 'X';
            ++mistakes;
            cout << (language == "deutsch" ? "Fehler " : "Mistake ") << mistakes << "/" << maxMistakes << endl;
        }

        gameWon = (playfield == pattern);
    }

    if (gameWon)
    {
        cout << (language == "deutsch" ? "Der Computer hat das Nonogram gelöst!" : "The computer solved the Nonogram!") << endl;
    }
    else
    {
        cout << (language == "deutsch" ? "Spiel vorbei. Der Computer hat zu viele Fehler gemacht." : "Game over. The computer made too many mistakes.") << endl;
    }

    saveGameHistory();
    updateHighScore();
}

void NonogramGame::gameSettings() 
{   
    int choice;
    bool check=true;
    do{
        cout << (language == "deutsch" ? "Wählen Sie den Schwierigkeitsgrad!!" : "Select the difficulty!") << endl;
        cout << "1. "<< (language == "deutsch" ? "Einfach" : "Easy") <<endl;
        cout << "2. "<< (language == "deutsch" ? "Mittel" : "Medium") <<endl;
        cout << "3. "<< (language == "deutsch" ? "Schwer" : "Hard") <<endl;
        cout << "Ihre Auswahl:";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << (language == "deutsch" ? "Ungültige Eingabe. Bitte geben Sie eine Zahl zwischen 1 und 3 ein." : "Invalid input. Please enter a number between 1 and 3.") << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            difficulty = "easy";
            break;
        case 2:
            difficulty = "medium";
            break;
        case 3:
            difficulty = "hard";
            break;
        default:
        {
            cout << (language == "deutsch" ? "Ungültige Auswahl. Bitte versuchen Sie es erneut." : "Invalid choice. Please try again.") << endl;
            check=false;
        }
        }
    } while (!check);
    pattern = NonogramPattern::generateRandomPattern(this->size, difficulty);
    rowHints = NonogramHints::calculateHints(pattern, true);
    colHints = NonogramHints::calculateHints(pattern, false);
    displayMenu();
}

void NonogramGame::saveGameHistory()
{
    NonogramHistory::saveGameHistory(playerName, field);
}

void NonogramGame::updateHighScore()
{
    NonogramHistory::updateHighScore(playerName);
}

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

NonogramGame::NonogramGame(int size, bool isTest,const std::string &difficulty)
    : size(isTest ? 5 : size), mistakes(0), maxMistakes(3), gameWon(false), difficulty(difficulty)
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
        cout << "1. " << "Spiel starten" << endl;
        cout << "2. " << "Testspiel starten (5x5)"<< endl;
        cout << "3. " << "Computerspiel starten"<< endl;
        cout << "4. " << "Bestenliste anzeigen"<< endl;
        cout << "5. " << "Regeln anzeigen"<< endl;
        cout << "6. " << "Spieleinstellungen" << endl;
        cout << "7. " << "Beenden" << endl;
        cout << "Ihre Auswahl:";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ungültige Eingabe. Bitte geben Sie eine Zahl zwischen 1 und 7 ein."<< endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            playGame();
            break;
        case 2:
        {
            NonogramGame testGame(5, true,difficulty);
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
            cout << "Spiel wird beendet. Auf Wiedersehen!"<< endl;
            break;
        default:
            cout << "Ungültige Auswahl. Bitte versuchen Sie es erneut."<< endl;
        }
    } while (choice != 6);
}

void NonogramGame::displayRules()
{
    cout << "----- Nonogram Regeln -----" << endl;
    cout << "1. " << "Das Spiel wird auf einem Gitter gespielt, Ziel ist es, ein verstecktes Muster zu enthüllen." << endl;
    cout << "2. " << "Zahlen in den Zeilen und Spalten zeigen an, wie viele aufeinanderfolgende Kästchen gefüllt sind."<< endl;
    cout << "3. " << "Es können mehrere Gruppen von gefüllten Kästchen durch leere Kästchen getrennt sein." << endl;
    cout << "4. " << "Das Spiel endet, wenn Sie 3 Fehler gemacht haben oder das Muster vervollständigt haben."<< endl;
    cout << "5. " << "Sie können jederzeit zwischen dem Markieren von gefüllten und leeren Kästchen wechseln."<< endl;
    cout << "6. " << "Am Ende des Spiels wird das versteckte Muster enthüllt."<< endl;
}

void NonogramGame::playGame()
{
    cout << "Geben Sie Ihren Namen ein: ";
    cin >> playerName;
    mistakes = 0;
    while (mistakes < maxMistakes && !gameWon)
    {
        NonogramDisplay::displayField(field, rowHints, colHints);
        cout << "Geben Sie Koordinaten (Zeile Spalte) zum Markieren ein: ";
        int row, col;
        cin >> row >> col;

        if (row < 0 || row >= size || col < 0 || col >= size)
        {
            cout << "Ungültige Koordinaten. Bitte geben Sie gültige Zahlen für Zeile und Spalte ein."<< endl;
            continue;
        }

        if (pattern[row][col] == '#')
        {
            field[row][col] = '#';
            playfield[row][col] = '#';
        }
        else
        {
            field[row][col] = 'X';
            ++mistakes;
            cout << "Fehler " << mistakes << "/" << maxMistakes << endl;
        }

        gameWon = (playfield == pattern);
    }

    if (gameWon)
    {
        cout << "Herzlichen Glückwunsch, Sie haben das Nonogram gelöst!"<< endl;
    }
    else
    {
        cout << "Spiel vorbei. Sie haben zu viele Fehler gemacht."<< endl;
    }

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
            cout << "Fehler "<< mistakes << "/" << maxMistakes << endl;
        }

        gameWon = (playfield == pattern);
    }

    if (gameWon)
    {
        cout << "Der Computer hat das Nonogram gelöst!" << endl;
    }
    else
    {
        cout << "Spiel vorbei. Der Computer hat zu viele Fehler gemacht." << endl;
    }

    saveGameHistory();
    updateHighScore();
}

void NonogramGame::gameSettings() 
{   
    int choice;
    bool check=true;
    do{
        cout << "Wählen Sie den Schwierigkeitsgrad!"<< endl;
        cout << "1. "<< "Einfach" <<endl;
        cout << "2. "<< "Mittel" <<endl;
        cout << "3. "<< "Schwer" <<endl;
        cout << "Ihre Auswahl:";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ungültige Eingabe. Bitte geben Sie eine Zahl zwischen 1 und 3 ein." << endl;
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
            cout << "Ungültige Auswahl. Bitte versuchen Sie es erneut." << endl;
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

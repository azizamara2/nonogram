#include "NonogramGame.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    bool isTest = false;
    string language;

    cout << "Choose language / Sprache auswählen:" << endl;
    cout << "1. English" << endl;
    cout << "2. Deutsch" << endl;
    int langChoice;
    cin >> langChoice;

    switch (langChoice)
    {
    case 1:
        language = "english";
        break;
    case 2:
        language = "deutsch";
        break;
    default:
        cout << "Invalid choice. Defaulting to English." << endl;
        language = "english";
    }

    NonogramGame game(10, isTest, language);
    game.displayMenu();

    return 0;
}
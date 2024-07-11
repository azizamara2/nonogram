#include "NonogramGame.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    bool isTest = false;

    NonogramGame game(10, isTest,"easy");
    game.displayMenu();

    return 0;
}
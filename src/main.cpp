#include <iostream>
#include <ctime>
#include "NonogramGame.h"

int main()
{
    srand(static_cast<unsigned int>(time(nullptr))); // Seed for random pattern generation
    NonogramGame game(10, false);
    game.displayMenu();
    return 0;
}
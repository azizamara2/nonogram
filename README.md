This git contains 2 branches: master and deutsch:
  - Master contains the game with a selection of the language : English or german.
  - Deutsch contains the german version of the game.
    
In order to compile and build the project you need to use the Makefile that supports both windows or linux OS. It will generate the game under /outputs/Nonogram (.exe for windows).
You can use the commands make or make clean to clean the directories.

  - NonogramPattern.cpp contains the definition of the function needed for the creation of a random pattern.
  - NonogramHistory.cpp is responsible for the save and update of highscores and game history.
  - NonogramHint.cpp is responsible for the calculation of the hints from the generated pattern.
  - NonogramDisplay.cpp Displays the field in a grid format.
  - NonogramGame.cpp contains the game engine, rules, main menu and different options:
      1. Play Game
      2. Play Test Game (5x5)
      3. Play Computer Game
      4. Display High Score
      5. Display Rules
      6. Settings
      7. Exit
  - main.cpp is only used to create an object from the class NonogramGame and call its functions to start the game.

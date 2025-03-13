//======================================================
// Project: Dice  File: main.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "tools.hpp"
#include "unitTests.hpp"
#include "Game.h"
#include "Player.hpp"

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    /*
    // Run dice unit test
    unitTests test;
    test.diceUnitTest();
    */

    /*
    // Run player unit test
    unitTests::playerUnitTest();
    */

    // Run column unit test
    // unitTests::columnUnitTest();

    /*
    // Run game unit test
    // unitTests::testGame();
    */
    
    // Run board unit test
    // unitTests::testBoard();

    Game game;
    game.oneTurn(&game.getPlayerOne());

    if (ifstream infile("output.txt"); infile) {
        string line;
        while (getline(infile, line)) {
            cout << line << endl;
        }
        infile.close();
    } else {
        cerr << "Error opening output.txt" << endl;
    }

    bye();  //Designates program termination
    return 0;
}

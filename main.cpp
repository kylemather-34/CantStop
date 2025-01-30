//======================================================
// Project: Dice  File: Dice.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Dice.h"
#include "Player.h"
#include "tools.hpp"
#include "unitTests.h"

using namespace std;

int main(int argc, char* argv[]) {
    srand(time(nullptr));
    banner();   //Prints names, date, and class
    unitTests test;
    test.diceUnitTest();

    unitTests test2;
    test2.playerUnitTest();

    Player player1("John", ECcolor::blue);  // Correct: Pass ECcolor::Red instead of an integer
    cout << player1;  // Print player details using the print method
    cout << "output.txt" << endl;
    bye();  //Designates program termination
    return 0;
}

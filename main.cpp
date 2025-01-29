//======================================================
// Project: Dice  File: Dice.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Dice.h"
#include "Player.h"
#include "tools.hpp"
#include "unitTests.h"
#include "tools.Cpp"

using namespace std;


int main() {
    srand(time(nullptr));
    banner();   //Prints names, date, and class
    unitTests test;
    test.diceUnitTest();

    Player player1("John", ECcolor::blue);  // Correct: Pass ECcolor::Red instead of an integer
    cout << player1;  // Print player details using the print method
    bye();  //Designates program termination
    return 0;
}

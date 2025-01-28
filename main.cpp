//======================================================
// Project: Dice  File: Dice.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Dice.h"
#include "unitTests.h"
#include "tools.hpp"

using namespace std;

int main() {
    srand(time(nullptr));
    banner();   //Prints names, date, and class
    /* Commented unit tests have been evaluated in previous weeks
    unitTests::diceUnitTest();
    */
    unitTests::playerUnitTest();
    bye();  //Designates program termination
    return 0;
}

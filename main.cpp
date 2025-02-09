//======================================================
// Project: Dice  File: main.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Dice.h"
#include "Player.h"
#include "tools.hpp"
#include "unitTests.h"

using namespace std;

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    // Run dice unit test
    unitTests test;
    test.diceUnitTest();

    // Run player unit test
    unitTests test2;
    test2.playerUnitTest();

    // Run column unit test
    unitTests test3;
    test3.columnUnitTest();

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

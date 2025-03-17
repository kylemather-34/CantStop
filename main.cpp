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




    unitTests::testPlayerList();

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

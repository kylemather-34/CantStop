//======================================================
// Project: Player  File: unitTests.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#include "unitTests.h"
#include "enums.h"
#include "Dice.h"
#include "Player.h"

/*diceUnitTest() function follows dice test plan in this directory to examine the
 *required input and output values, edge cases, and potential errors
*/
void unitTests::diceUnitTest() {
    ofstream outFile("Output.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    // Test Initialization
    outFile << "Test Initialization: Dice\n";
    Dice d1(6);

    // Test Rolling Dice
    outFile << "Test Rolling Dice:\n";
    const int* values = d1.roll();
    outFile << "Dice values: ";
    // Prints out values of dice
    for (int i = 0; i < 6; ++i) {
        outFile << values[i] << " ";
        // Check if values are between 1 and 6
        if (values[i] < 1 || values[i] > 6) {
            outFile << "\nError: Dice value out of range!";
        }
    }
    outFile << endl;

    // Test Printing Dice Values
    outFile << "Test Printing Dice Values:\n";
    outFile << "Dice values printed: ";
    d1.print(outFile);
    outFile << endl;
    //outFile << "Dice values printed: " << d1 << endl;

    // Test Destructor
    outFile << "Test Destructor:\n";
    {
        Dice d2(10);
    } // d2 should be destroyed here
    outFile << "No explicit output; check for memory leaks.\n";
    // Closing output file
    outFile.close();
}
/*
ofstream operator<<(const ofstream & lhs, ECcolor rhs);

void unitTests::playerUnitTest() {
    ofstream outFile("Output.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    outFile << "Test Initialization: Player\n";

    Player player("Test Player", ECcolor::white);
    outFile << "Player Color: ";
    outFile << player.color() << endl;
    outFile << player.score() << endl;
    outFile << "Testing winColumn() function:" << endl;
    for (int y = 1; y <=3; ++y) {
        outFile << player.wonColumn(1) << endl;
    }

    outFile.close();
}
*/
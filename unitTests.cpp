//======================================================
// Project: Player  File: unitTests.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#include "tools.hpp"
#include "unitTests.h"
#include "enums.h"
#include "Dice.h"
#include "Player.h"
#include "Column.h"

/*diceUnitTest() function follows dice test plan in this directory to examine the
 *required input and output values, edge cases, and potential errors
*/
void unitTests::diceUnitTest() {
    ofstream outFile("Output.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    fbanner(outFile);
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
    outFile << "Dice values printed: " << d1 << endl;

    // Test Destructor
    outFile << "Test Destructor:\n";
    {
        Dice d2(10);
    } // d2 should be destroyed here
    outFile << "No explicit output; check for memory leaks.\n";
    // Closing output file
    outFile.close();
}


/*playerUnitTest() function tests Player class functionality
 *It initalizes a Player object, prints details, and tests column wins.
 */
void unitTests::playerUnitTest() {
    ofstream outFile("Output.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    outFile << "\nTest Initialization: Player\n";

    Player player("Test Player", ECcolor::white);
    outFile << player;
    outFile << "Testing winColumn() function:" << endl;
    for (int y = 1; y <=3; ++y) {
        outFile << player.wonColumn(1) << endl;
    }

    outFile.close();
}

void unitTests::columnUnitTest() {
    ofstream outFile("Output.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    outFile << "\nTest Initialization: Column\n";

    // Test valid column creation
    Column column(5);
    outFile  << "Column state: " << column.colStateToString(column.state()) << endl;

    // Test starting tower on column
    Player player("Test Player", ECcolor::blue);
    outFile << "Starting tower on column 5: " << column.startTower(&player) << endl;
    outFile << "Column marker positions after startTower: ";
    const int* positions = column.getMarkerPositions();
    for (int y = 0; y < static_cast<int>(ECcolor::Count); ++y) {
        outFile << positions[y] << " ";
    }
    outFile << endl;

    // Test move function
    outFile << "Moving tower on column 5: " << column.move() << endl;
    outFile << "Column marker positions after move: ";
    for (int y = 0; y < static_cast<int>(ECcolor::Count); ++y) {
        outFile << positions[y] << " ";
    }
    outFile << endl;

    // Test stop function
    column.stop(&player);  // Stop the player's turn and apply changes
    outFile << "Column marker positions after stop: ";
    for (int y = 0; y < static_cast<int>(ECcolor::Count); ++y) {
        outFile << positions[y] << " ";
    }
    outFile << endl;

    // Test column print function
    outFile << "Printing column state after stop:\n";
    std::ostringstream os;
    column.print(os);
    outFile << os.str() << endl;

    outFile.close();
}

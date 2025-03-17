//======================================================
// Project: Player  File: unitTests.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#include "unitTests.hpp"
#include "enums.hpp"
#include "Dice.hpp"
#include "Player.hpp"
#include "Column.hpp"
#include "Game.h"
#include "Board.hpp"
#include "CList.h"
#include <memory>

/*diceUnitTest() function follows dice test plan in this directory to examine the
 required input and output values, edge cases, and potential errors
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
 It initalizes a Player object, prints details, and tests column wins.
 */
void unitTests::playerUnitTest() {
    ofstream outFile("Output.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    fbanner(outFile);
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

    fbanner(outFile);
    outFile << "\nTest Initialization: Column\n";

    // Test valid column creation
    Column column(5);
    outFile  << "Column state: " << column.colStateToString(column.state()) << endl;

    // Test starting tower on column
    Player player("Test Player", ECcolor::blue);
    outFile << "Starting tower on column 5: " << column.startTower(&player) << endl;
    outFile << "Column marker positions after startTower: ";
    const int* positions = column.getMarkerPositions();
    for (int y = 0; y < (int)ECcolor::Count; ++y) {
        outFile << positions[y] << " ";
    }
    outFile << endl;

    // Test move function
    outFile << "Moving tower on column 5: " << column.move() << endl;
    outFile << "Column marker positions after move: ";
    for (int y = 0; y < (int)ECcolor::Count; ++y) {
        outFile << positions[y] << " ";
    }
    outFile << endl;

    // Test stop function
    column.stop(&player);  // Stop the player's turn and apply changes
    outFile << "Column marker positions after stop: ";
    for (int y = 0; y < (int)ECcolor::Count; ++y) {
        outFile << positions[y] << " ";
    }
    outFile << endl;

    // Test column print function
    outFile << "Printing column state after stop:\n";
    ostringstream os;
    column.print(os);
    outFile << os.str() << endl;

    outFile.close();
}

void unitTests::testGame() {
    ofstream outFile("Output.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    fbanner(outFile);
    outFile << "\nTest Initialization: Game\n";

    Game game;  // Create a game instance


    outFile << "\nTesting Dice Rolling:\n";
    for (int y = 0; y < 4; ++y) {
        outFile << "Die " << (y+1) << " rolled: ";
        game.getDice()[y].roll();
        outFile << game.getDice()[y] << endl;
    }

    // Test player initialization
    outFile << "\nTesting Player Initialization:\n";
    outFile << "Player 1: ";
    game.getPlayerOne().print(outFile);
    outFile << "Player 2: ";
    game.getPlayerTwo().print(outFile);

    // Test column initialization
    outFile << "\nTesting Column Initialization:\n";
    outFile << "Column 1 (length 2) created.\n";
    outFile << "Column 2 (length 7) created.\n";

    // Test placing a tower in column 7
    outFile << "\nTesting Tower Placement on Column 7:\n";
    Column& col = game.getColumnTwo();
    outFile << "Starting tower on column 7: " << col.startTower(&game.getPlayerOne()) << endl;

    // Test column marker positions after tower start
    outFile << "Column marker positions after startTower: ";
    const int* positions = col.getMarkerPositions();
    for (int y = 0; y < (int)ECcolor::Count; ++y) {
        outFile << positions[y] << " ";
    }
    outFile << endl;

    // Test moving tower
    outFile << "\nTesting Tower Move on Column 7:\n";
    outFile << "Moving tower: " << col.move() << endl;

    outFile << "Column marker positions after move: ";
    for (int y = 0; y < (int)ECcolor::Count; ++y) {
        outFile << positions[y] << " ";
    }
    outFile << endl;

    // Test stopping the column
    outFile << "\nTesting Column Stop:\n";
    col.stop(&game.getPlayerOne());

    outFile << "Column marker positions after stop: ";
    for (int y = 0; y < (int)ECcolor::Count; ++y) {
        outFile << positions[y] << " ";
    }
    outFile << endl;

    // Test column print function
    outFile << "\nPrinting Column 7 State After Stop:\n";
    ostringstream os;
    col.print(os);
    outFile << os.str() << endl;

    outFile.close();
}

void unitTests::testPlayerList() {
    // Create a CList of unique pointers to Players
    CList playerList;

    // Test 1: Add Players to the list
    cout << "=== Test 1: Adding Players ===" << endl;
    playerList.addCell(new Cell(make_unique<Player>(1, "Alice")));
    playerList.addCell(new Cell(make_unique<Player>(2, "Bob")));
    playerList.addCell(new Cell(make_unique<Player>(3, "Charlie")));
    playerList.addCell(new Cell(make_unique<Player>(4, "Diana")));
    playerList.print();
    cout << "Number of players: " << playerList.getCount() << endl;
    cout << endl;

    // Test 2: Remove a Player and verify the list remains functional
    cout << "=== Test 2: Removing a Player ===" << endl;
    playerList.init(); // Set current to head
    playerList.next(); // Move to the first player (Alice)
    playerList.remove(); // Remove Alice
    playerList.print();
    cout << "Number of players: " << playerList.getCount() << endl;
    cout << endl;

    // Test 3: Remove all Players and verify the list is empty
    cout << "=== Test 3: Removing All Players ===" << endl;
    while (!playerList.empty()) {
        playerList.remove();
    }
    playerList.print();
    cout << "Number of players: " << playerList.getCount() << endl;
    cout << endl;

    // Test 4: Add Players again after removing all
    cout << "=== Test 4: Adding Players Again ===" << endl;
    playerList.addCell(new Cell(make_unique<Player>(5, "Eve")));
    playerList.addCell(new Cell(make_unique<Player>(6, "Frank")));
    playerList.print();
    cout << "Number of players: " << playerList.getCount() << endl;
    cout << endl;

    // Test 5: Traverse the list using nextPlayer()
    cout << "=== Test 5: Traversing the List ===" << endl;
    playerList.init(); // Set current to head
    for (int i = 0; i < playerList.getCount() * 2; ++i) { // Traverse twice
        Cell* currentCell = playerList.next();
        cout << "Current Player: ";
        currentCell->upp->print();
    }
    cout << endl;

    // Test 6: Print an empty list
    cout << "=== Test 6: Printing an Empty List ===" << endl;
    while (!playerList.empty()) {
        playerList.remove();
    }
    playerList.print();
    cout << "Number of players: " << playerList.getCount() << endl;

    return 0;
}

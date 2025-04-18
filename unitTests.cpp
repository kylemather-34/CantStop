//======================================================
// Project: Can't Stop  File: unitTests.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#include "unitTests.hpp"
#include "enums.hpp"
#include "Dice.hpp"
#include "Player.hpp"
#include "Column.hpp"
#include "Game.hpp"
#include "Board.hpp"
#include "CList.hpp"
#include <memory>

void unitTests::testPlayerList() {
    ofstream outFile("Output.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    fbanner(outFile);
    // Create a CList of unique pointers to Players
    CList playerList;

    // Test 1: Add Players to the list
    outFile << "=== Test 1: Adding Players ===" << endl;

    playerList.addCell("Alice", ECcolor::blue);
    playerList.addCell("Bob", ECcolor::green);
    playerList.addCell("Charlie", ECcolor::orange);
    playerList.addCell("Diana", ECcolor::yellow);
    playerList.print(outFile);
    outFile << "Number of players: " << playerList.getCount() << endl;
    outFile<< endl;

    // Test 2: Remove a Player and verify the list remains functional
    outFile << "=== Test 2: Removing a Player ===" << endl;
    playerList.init(); // Set current to head
    playerList.next(); // Move to the first player (Alice)
    playerList.remove(); // Remove Alice
    outFile << playerList << endl;
    outFile << "Number of players: " << playerList.getCount() << endl;
    outFile << endl;

    // Test 3: Remove all Players and verify the list is empty
    outFile << "=== Test 3: Removing All Players ===" << endl;
    while (!playerList.empty()) {
        playerList.remove();
    }
    // playerList.print();
    outFile << "Number of players: " << playerList.getCount() << endl;
    outFile << endl;

    // Test 4: Add Players again after removing all
    outFile << "=== Test 4: Adding Players Again ===" << endl;
    playerList.addCell("Eve", ECcolor::blue);
    playerList.addCell("Frank", ECcolor::orange);
    playerList.print(outFile);
    outFile << "Number of players: " << playerList.getCount() << endl;
    outFile << endl;

    // Test 5: Traverse the list using nextPlayer()
    outFile << "=== Test 5: Traversing the List ===" << endl;
    playerList.init(); // Set current to head
    for (int y = 0; y < playerList.getCount(); ++y) {
        // Traverse twice
        Cell* currentCell = playerList.next();
        Player* currentPlayer = playerList.getCurrentPlayer(); // Get Player from the list
        if (currentPlayer) {
            outFile << "Current Player: " << currentPlayer->getName() << endl; // Use Player's methods
        }
    }
    outFile << endl;

    // Test 6: Print an empty list
    outFile << "=== Test 6: Printing an Empty List ===" << endl;
    while (!playerList.empty()) {
        playerList.remove();
    }
    playerList.print(outFile);
    outFile << "Number of players: " << playerList.getCount() << endl;

    outFile.close();
}

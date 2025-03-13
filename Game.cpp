//======================================================
// Project: Player  File: Game.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#include "Game.h"
#include "enums.hpp"

// Constructor
Game::Game() :
    cOne(2), cTwo(7),
    pOne(getNewPlayer()), pTwo(getNewPlayer()),
    fourDice(nullptr), board()
{
    fourDice = new Dice[4];
}

Game::~Game() {
    delete[] fourDice; // Free allocated dice array
}


/* getNewPlayer function inputs player's data from keyboard
 * and calls the constructor */
Player Game::getNewPlayer() {
    string name;
    char colorChar;
    ECcolor color;

    cout << "Enter player name: ";
    cin >> name;
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    cout << "Enter letter of color (o. orange, y. yellow, g. green, b. blue): ";
    cin >> colorChar;

    colorChar = tolower(colorChar);

    switch (colorChar) {
        case 'o':
            color = ECcolor::orange;
            break;
        case 'y':
            color = ECcolor::yellow;
            break;
        case 'g':
            color = ECcolor::green;
            break;
        case 'b':
            color = ECcolor::blue;
            break;
        default:
            cout << "Invalid color! Defaulting to blue.\n";
            color = ECcolor::blue;
    }

    return Player(name, color);
}

void Game::oneTurn(Player* pp) {
    board.startTurn(pp);  // Start turn for the player

    cout << "Player " << pp->getName() << " is first." << endl;


    while (true) {
        int towersPlaced = 0;
        
        // Display menu
        cout << "Pick a choice (Use the # associated with the choice):\n";
        cout << "1. Roll  2. Stop  3. Resign" << endl;
        int choice;
        cin >> choice;

        if (choice == 2) {  // Stop turn
            board.stop();
            break;
        }
        else if (choice == 1) {  // Roll dice
            if (!fourDice) {  // Ensure the dice object exists
                cout << "Error: Dice not initialized!" << endl;
                return;
            }
        
            const int* rollResults = fourDice->roll();  // Get roll values

            cout << "Rolled Dice: ";
            char diceLabels[4] = {'A', 'B', 'C', 'D'};

            for (int y = 0; y < 4; y++) {
                cout << diceLabels[y] << ": " << rollResults[y] << "  ";
            }
            cout << endl;

            // Get user selection for dice pairs
            char first, second;
            bool isValid = false;
            while (!isValid) {
                cout << "Choose a pair using letters (e.g., AC): ";
                cin >> first >> second;
                first = toupper(first);
                second = toupper(second);
                if (first != second &&
                   (first == 'A' || first == 'B' || first == 'C' || first == 'D') &&
                   (second == 'A' || second == 'B' || second == 'C' || second == 'D')) {
                    isValid = true;
                   } else {
                       cout << "Invalid selection. Choose two different dice (A, B, C, D).\n";
                   }
            }

            int firstIndex = first - 'A';
            int secondIndex = second - 'A';

            // Calculate the column numbers based on the selected dice pairs
            int column1 = rollResults[firstIndex] + rollResults[secondIndex];

            int remainingIndex[2], count = 0;
            for (int k = 0; k < 4; k++) {
                if (k != firstIndex && k != secondIndex) {
                    remainingIndex[count++] = k;
                }
            }
            int column2 = rollResults[remainingIndex[0]] + rollResults[remainingIndex[1]];

            // Attempt to move towers
            bool move1, move2;
            if (towersPlaced == 2) {
                cout << "Reordering moves due to last tower placement rule.\n";
                move2 = board.move(column2);
                move1 = board.move(column1);
            } else {
                move1 = board.move(column1);
                move2 = board.move(column2);
            }

            cout << "\nMove Results:\n";
            cout << "First Move (" << column1 << "): " <<
                (move1 ? "Success" : "Failed") << endl;
            cout << "Second Move (" << column2 << "): " <<
                (move2 ? "Success" : "Failed") << endl;

            // Check if the player went bust
            if (!move1 && !move2) {
                cout << "Bust! No valid moves." << endl;
                board.bust();
                break;
            }

            // Print the board after moving
            board.print();

            // Check for column captures
            if (move1 && board.getColumn(column1)->isCaptured()) {
                cout << "Column " << column1 << " captured!" << endl;
                pp->wonColumn(column1);
            }
            if (move2 && board.getColumn(column2)->isCaptured()) {
                cout << "Column " << column2 << " captured!" << endl;
                pp->wonColumn(column2);
            }

            // Check if the player has won
            if (pp->score() >= 3) {
                cout << "Player " << pp->getName() << " has won the game!" << endl;
                return;
            }
        }
        else if (choice == 3) {
            cout << "Resign option not implemented yet." << endl;
            break;
        }
        else {
            cout << "Invalid option. Try again." << endl;
        }
    }
}
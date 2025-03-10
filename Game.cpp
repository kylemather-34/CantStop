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

    while (true) {
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

            fourDice->roll();  // Roll the dice
            const int* rollResults = fourDice->getDice();  // Get roll values

            cout << "Rolled Dice: ";
            char diceLabels[4] = {'A', 'B', 'C', 'D'};

            for (int i = 0; i < 4; i++) {
                cout << diceLabels[i] << ": " << rollResults[i] << "  ";
            }
            cout << endl;

            // Get user selection for dice pairs
            string input;
            cout << "Choose a pair using letters (e.g., AC): ";
            cin >> input;

            if (input.length() != 2) {
                cout << "Invalid selection. Enter two letters." << endl;
                continue;
            }

            char first = toupper(input[0]);
            char second = toupper(input[1]);

            int firstIndex = first - 'A';
            int secondIndex = second - 'A';

            if (firstIndex < 0 || firstIndex >= 4 || secondIndex < 0 || secondIndex >= 4 || firstIndex == secondIndex) {
                cout << "Invalid selection. Try again." << endl;
                continue;
            }

            // Calculate the column numbers based on the selected dice pairs
            int column1 = rollResults[firstIndex] + rollResults[secondIndex];
            int column2 = -1;

            // Calculate the second pair
            for (int i = 0; i < 4; i++) {
                if (i != firstIndex && i != secondIndex) {
                    if (column2 == -1) {
                        column2 = rollResults[i];
                    } else {
                        column2 += rollResults[i];
                    }
                }
            }

            // Check if the columns are valid (between 2 and 12)
            if (column1 < 2 || column1 > 12 || column2 < 2 || column2 > 12) {
                cout << "Invalid column numbers. Try again." << endl;
                continue;
            }

            // Attempt to move towers
            bool move1 = board.move(column1);
            bool move2 = board.move(column2);

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
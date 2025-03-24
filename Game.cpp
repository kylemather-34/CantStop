//======================================================
// Project: Can't Stop  File: Game.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#include "Game.h"
#include "enums.hpp"
#include "tools.hpp"


// Constructor
Game::Game() :
    cOne(2), cTwo(7), fourDice(nullptr), board()
{
    fourDice = new Dice[4];

    // Add players to the CList instead of storing them directly
    int numOfPlayers;
    cout << "Please input your number of players (2-4): ";
    while (!(cin >> numOfPlayers) || numOfPlayers < 2 || numOfPlayers > 4) {
        cout << "Invalid input. Please enter a number between 2 and 4: ";
        cin.clear();  // Clear error flag
        cin.ignore(10000, '\n');  // Discard invalid input
    }


    for (int x = 0; x < numOfPlayers; x++) {
        addPlayer();
    }

    players.init(); // Set current to head

    while (true) {
        Player* currentPlayer = players.getCurrentPlayer(); // Get Player from the list
        if (currentPlayer) {
            oneTurn(currentPlayer);
            cout << "Current Player: " << currentPlayer->getName() << endl; // Use Player's methods
        }
        Cell* currentCell = players.next();
    }
}



void Game::addPlayer() {
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
        case 'o': color = ECcolor::orange; break;
        case 'y': color = ECcolor::yellow; break;
        case 'g': color = ECcolor::green; break;
        case 'b': color = ECcolor::blue; break;
        default:
            cout << "Invalid color! Defaulting to blue.\n";
        color = ECcolor::blue;
    }

    // Use CList's addCell to create and store the player
    players.addCell(name, color);
}

void Game::oneTurn(Player* pp) {
    board.startTurn(pp);
    cout << "The current board is: " << board << endl;

    while (true) {
        cout << "Pick a choice (Use the # associated with the choice):\n";
        cout << "1. Roll  2. Stop  3. Resign" << endl;
        int choice;
        cin >> choice;

        if (choice == 2) {  // Stop turn
            board.stop();
            break;
        }
        else if (choice == 1) {  // Roll dice
            const int* rollResults = fourDice->roll();
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

            // Calculate first column (sum of selected dice)
            int firstIndex = first - 'A';
            int secondIndex = second - 'A';
            int cl = rollResults[firstIndex] + rollResults[secondIndex];

            // Calculate second column (sum of remaining dice)
            int cl2 = 0;
            for (int y = 0; y < 4; y++) {
                if (y != firstIndex && y != secondIndex) {
                    cl2 += rollResults[y];
                }
            }

            // Attempt moves
            bool move1 = board.move(cl);
            bool move2 = board.move(cl2);

            cout << "\nMove Results:\n";
            cout << "Move (" << cl << "): " << (move1 ? "Success" : "Failed") << endl;
            cout << "Move (" << cl2 << "): " << (move2 ? "Success" : "Failed") << endl;

            // Only bust if both moves fail
            if (!move1 && !move2) {
                cout << "Bust! No valid moves." << endl;
                board.bust();
                break;
            }

            // Print the board after moving
            cout << board << endl;

            // Check for column captures
            if (move1 && board.getColumn(cl)->isCaptured()) {
                cout << "Column " << cl << " captured!" << endl;
                pp->wonColumn(cl);
            }
            if (move2 && board.getColumn(cl2)->isCaptured()) {
                cout << "Column " << cl2 << " captured!" << endl;
                pp->wonColumn(cl2);
            }

            // Check for win condition
            if (pp->score() >= 3) {
                cout << "Player " << pp->getName() << " has won the game!" << endl;
                return;
            }
        }
        else if (choice == 3) { // Resign
            break;
        }
        else {
            cout << "Invalid option. Try again." << endl;
        }
    }
}
/*void Game::oneTurn(Player* pp) {
    board.startTurn(pp);  // Start turn for the player
    cout << "The current board is: " << board << endl;
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
                    // Ensure the dice values are greater than 0
                    if (rollResults[first - 'A'] > 0 && rollResults[second - 'A'] > 0) {
                        isValid = true;
                    } else {
                        cout << "Invalid selection. Dice values must be greater than 0.\n";
                    }
                } else {
                    cout << "Invalid selection. Choose two different dice (A, B, C, D).\n";
                }
            }

            int firstIndex = first - 'A';
            int secondIndex = second - 'A';

            // Calculate the column numbers based on the selected dice pairs
            int cl = rollResults[firstIndex] + rollResults[secondIndex];

            int remainingIndex[2], count = 0;
            for (int k = 0; k < 4; k++) {
                if (k != firstIndex && k != secondIndex) {
                    remainingIndex[count++] = k;
                }
            }
            int cl2 = rollResults[remainingIndex[0]] + rollResults[remainingIndex[1]];

            bool move1, move2;

            move1 = board.move(cl);
            move2 = board.move(cl2);

            cout << "\nMove Results:\n";
            cout << "Move (" << cl << "): " <<
                (move1 ? "Success" : "Failed") << endl;
            cout << "Move (" << cl2 << "): " <<
                (move2 ? "Success" : "Failed") << endl;

            // Check if the player went bust
            if (!move1 || !move2) {
                cout << "Bust! No valid moves." << endl;
                board.bust();
                break;
            }

            // Print the board after moving
            board.print();

            // Check for column captures
            if (move1 && board.getColumn(cl)->isCaptured()) {
                cout << "Column " << cl << " captured!" << endl;
                pp->wonColumn(cl);
            } else if (move2 && board.getColumn(cl2)->isCaptured()) {
                cout << "Column " << cl2 << " captured!" << endl;
            }

            // Check if the player has won
            if (pp->score() >= 3) {
                cout << "Player " << pp->getName() << " has won the game!" << endl;
                break;  // Exit the game loop since we have a winner
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
}*/


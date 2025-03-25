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

void Game::oneTurn(Player* currentPlayer) {
    board.startTurn(currentPlayer);
    cout << "The current board is:\n" << board << endl;
    cout << "Player " << currentPlayer->getName() << "'s turn.\n";

    bool keepRolling = true;
    while (keepRolling) {
        cout << "1. Roll  2. Stop  3. Resign\n";
        int choice;
        cin >> choice;

        if (choice == 2) { // Stop
            board.stop();
            cout << "Turn ended. Final positions:\n" << board << endl;
            keepRolling = false;
        }
        else if (choice == 1) { // Roll
            const int* dice = fourDice->roll();
            cout << "Rolled: A:" << dice[0] << " B:" << dice[1]
                 << " C:" << dice[2] << " D:" << dice[3] << endl;

            // Get dice pair selection
            char pair1, pair2;
            cout << "Choose first pair (e.g. AB): ";
            cin >> pair1 >> pair2;
            pair1 = toupper(pair1);
            pair2 = toupper(pair2);

            // Calculate column numbers
            int col1 = dice[pair1-'A'] + dice[pair2-'A'];

            // Calculate second pair automatically
            int unused1 = (pair1 == 'A' || pair2 == 'A') ? 0 : 'A'-'A';
            int unused2 = (pair1 == 'B' || pair2 == 'B') ? 0 : 'B'-'A';
            if (unused1 == unused2) {
                unused2 = (pair1 == 'C' || pair2 == 'C') ? 0 : 'C'-'A';
            }
            int col2 = dice[unused1] + dice[unused2];

            // Attempt moves
            bool move1 = board.move(col1);
            bool move2 = board.move(col2);

            cout << "Attempting moves: " << col1 << " and " << col2 << endl;
            cout << "Move " << col1 << ": " << (move1 ? "Success" : "Failed") << endl;
            cout << "Move " << col2 << ": " << (move2 ? "Success" : "Failed") << endl;

            if (!move1 && !move2) {
                cout << "BUST! No valid moves.\n";
                board.bust();
                cout << "Current board:\n" << board << endl;
                keepRolling = false;
            }
            else {
                cout << "Current board (T = temporary):\n" << board << endl;

                // Check for captured columns
                if (move1 && board.getColumn(col1)->isCaptured()) {
                    currentPlayer->wonColumn(col1);
                    cout << "COLUMN " << col1 << " CAPTURED!\n";
                }
                if (move2 && board.getColumn(col2)->isCaptured()) {
                    currentPlayer->wonColumn(col2);
                    cout << "COLUMN " << col2 << " CAPTURED!\n";
                }

                // Check win condition
                if (currentPlayer->score() >= 3) {
                    cout << "PLAYER " << currentPlayer->getName() << " WINS!\n";
                    keepRolling = false;
                }
            }
        }
        else if (choice == 3) { // Resign
            cout << currentPlayer->getName() << " resigns.\n";
            board.bust();
            keepRolling = false;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}



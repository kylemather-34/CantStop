//======================================================
// Project: Can't Stop  File: Game.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#include "Game.h"
#include "enums.hpp"
#include "tools.hpp"

// Constructor
Game::Game() :
    cOne(2), cTwo(7), CSDice(nullptr), board()
{
    CSDice = new CantStopDice();

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

    while (players.getCount() >= 2) {
        Player* currentPlayer = players.getCurrentPlayer(); // Get Player from the list
        if (!currentPlayer) break;
        if (currentPlayer) {
            takeTurn(currentPlayer);
            cout << "Current Player: " << currentPlayer->getName() << "\n";// Use Player's methods
        }
        Cell* currentCell = players.next();
    }
}

void Game::addPlayer() {
    string name;
    char colorChar;
    ECcolor color;
    bool colorAvailable;

    // Get player name
    cout << "Enter player name: ";
    cin >> name;
    transform(name.begin(), name.end(), name.begin(), ::tolower);

    do {
        colorAvailable = true;

        // Get color choice
        cout << "Enter letter of color (o. orange, y. yellow, g. green, b. blue): ";
        cin >> colorChar;
        colorChar = tolower(colorChar);

        // Validate color choice
        switch (colorChar) {
            case 'o': color = ECcolor::orange; break;
            case 'y': color = ECcolor::yellow; break;
            case 'g': color = ECcolor::green; break;
            case 'b': color = ECcolor::blue; break;
            default:
                cout << "Invalid color! Please choose from o,y,g,b.\n";
                colorAvailable = false;
                continue;
        }

        // Check if color is already taken
        if (players.getCount() > 0) {
            players.init(); // Reset to head of list
            for (int i = 0; i < players.getCount(); i++) {
                Player* existingPlayer = players.getCurrentPlayer();
                if (existingPlayer) {

                    if (existingPlayer->color() == color) {
                        cout << "Color already taken by " << existingPlayer->getName() << "!\n";
                        colorAvailable = false;
                        break;
                    }
                }
                players.next();
            }
        }

    } while (!colorAvailable);

    // Add the player with validated color
    players.addCell(name, color);
}

void Game::takeTurn(Player* currentPlayer) {
    board.startTurn(currentPlayer);
    cout << "\nThe current board is:\n" << board << endl;
    cout << "Player " + currentPlayer->getName() + "'s turn.\n";

    bool keepRolling = true;
    while (keepRolling) {
        cout << "\nOptions: 1. Roll  2. Stop  3. Resign\nChoice: ";
        int choice;
        cin >> choice;

        if (choice == 2) { // Stop
            board.stop();
            cout << "\nTurn ended. Final positions:\n";
            board.print();
            keepRolling = false;
        }
        else if (choice == 1) { // Roll
            const int* dice = CSDice->roll(); // Use CantStopDice::roll() to handle dice rolls

            int col1 = dice[0];
            int col2 = dice[1];

            // Attempt moves
            bool move1 = board.move(col1);
            bool move2 = board.move(col2);

            cout << "\nAttempting moves: " << col1 << " and " << col2 << endl;
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
            cout << "\n"<<currentPlayer->getName() << " resigns.\n";
            board.bust();

            cout << endl;
            players.init(); // Set current to head
            players.remove();
            cout << endl;
            cout << "Number of players left: " << players.getCount() << endl;
            cout << endl;

            if (players.getCount() < 2) {
                cout << "Not enough players, ending the game!" << endl;
                cout << *players.getCurrentPlayer() << "WINS!\n";
                keepRolling = false;
                while (!players.empty()) {
                    players.remove();
                }
                return;
            }
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}
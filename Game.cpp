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

    while (players.getCount() >= 2) {
        Player* currentPlayer = players.getCurrentPlayer(); // Get Player from the list
        if (currentPlayer) {
            takeTurn(currentPlayer);
            cout << "Current Player: " << currentPlayer->getName() << endl; // Use Player's methods
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
    cout << "The current board is:\n" << board << endl;
    cout << "Player " << currentPlayer->getName() << "'s turn.\n";

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
            const int* dice = fourDice->roll();
            cout << "\nRolled Dice:\n";
            cout << "A: " << dice[0] << "  B: " << dice[1]
                 << "  C: " << dice[2] << "  D: " << dice[3] << "\n";

            // Get dice pair selection
            char pair1, pair2;
            bool valid = false;
            while (!valid) {
                cout << "Choose first pair (e.g. AB): ";
                cin >> pair1 >> pair2;
                pair1 = toupper(pair1);
                pair2 = toupper(pair2);

                if (pair1 != pair2 &&
                    (pair1 == 'A' || pair1 == 'B' || pair1 == 'C' || pair1 == 'D') &&
                    (pair2 == 'A' || pair2 == 'B' || pair2 == 'C' || pair2 == 'D')) {
                    valid = true;
                } else {
                    cout << "Invalid selection. Choose two different dice (A-D).\n";
                }
            }

            // Calculate first column
            int col1 = dice[pair1-'A'] + dice[pair2-'A'];
            // Calculate second column from remaining dice
            int remainingIndices[2];
            int idx = 0;
            for (int i = 0; i < 4; i++) {
                if (i != (pair1-'A') && i != (pair2-'A')) {
                    remainingIndices[idx++] = i;
                }
            }
            int col2 = dice[remainingIndices[0]] + dice[remainingIndices[1]];

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
            keepRolling = false;

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
            }

        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}



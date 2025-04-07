//======================================================
// Project: Can't Stop  File: Game.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#include "Game.h"
#include "enums.hpp"
#include "tools.hpp"
#include "Exceptions.h"
#include <cstring>
#include <thread>

// Constructor
Game::Game() :
    cOne(2), cTwo(7), CSDice(nullptr), board()
{
    CSDice = new CantStopDice();

    // Add players to the CList
    int numOfPlayers;
    cout << "Please input your number of players (2-4): ";
    while (!(cin >> numOfPlayers) || numOfPlayers < 2 || numOfPlayers > 4) {
        cout << "Invalid input. Please enter a number between 2 and 4: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    for (int x = 0; x < numOfPlayers; x++) {
        addPlayer();
    }

    players.init(); // Set current to head

    while (players.getCount() >= 2) {
        Player* currentPlayer = players.getCurrentPlayer();
        if (!currentPlayer) break;
        takeTurn(currentPlayer);
        players.next();
    }
}

void Game::validDice(const string& selection) {
    const char* validChoices = "abcdABCD";

    if (selection.length() != 2) {
        throw BadSlot(selection);
    }

    char first = tolower(selection[0]);
    char second = tolower(selection[1]);

    if (strchr(validChoices, first) == nullptr ||
        strchr(validChoices, second) == nullptr) {
        throw BadSlot(selection);
    }

    if (first == second) {
        throw DuplicateSlot(selection);
    }
}

void Game::validMenu(const int& input) {
    if (input < 1 || input > 3) {
        throw BadChoice(to_string(input));
    }
}

void Game::addPlayer() {
    string name;
    char colorChar;
    ECcolor color;

    while (true) { // Main player addition loop
        // Get and validate name
        cout << "Enter player name: ";
        while (true) {
            try {
                if (!(cin >> name)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    throw BadChoice("Invalid name input");
                }

                // Check for duplicate names
                bool nameTaken = false;
                if (players.getCount() > 0) {
                    players.init();
                    for (int x = 0; x < players.getCount(); x++) {
                        Player* existingPlayer = players.getCurrentPlayer();
                        if (existingPlayer) {
                            string existingName = existingPlayer->getName();
                            transform(existingName.begin(), existingName.end(),
                                     existingName.begin(), ::tolower);
                            string inputName = name;
                            transform(inputName.begin(), inputName.end(),
                                     inputName.begin(), ::tolower);

                            if (existingName == inputName) {
                                nameTaken = true;
                                break;
                            }
                        }
                        players.next();
                    }
                }

                if (nameTaken) {
                    throw BadName(name, ' ');
                }
                break; // Valid name
            }
            catch (const BadName& e) {
                e.print();
                cin.clear();
                cin.ignore(10000, '\n');
            }
            catch (const BadChoice& e) {
                cout << "Invalid name format. Please try again.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }

        cout << "Enter letter of color (o. orange, y. yellow, g. green, b. blue): ";
        // Get and validate color
        bool colorValid = false;
        while (!colorValid) {
            try {
                if (!(cin >> colorChar)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    throw BadChoice("Invalid color input");
                }
                colorChar = tolower(colorChar);

                // Validate color format
                switch (colorChar) {
                    case 'o': color = ECcolor::orange; break;
                    case 'y': color = ECcolor::yellow; break;
                    case 'g': color = ECcolor::green; break;
                    case 'b': color = ECcolor::blue; break;
                    default:
                        throw BadChoice("Invalid color choice");
                }

                // Check for duplicate colors
                bool colorTaken = false;
                if (players.getCount() > 0) {
                    players.init();
                    for (int x = 0; x < players.getCount(); x++) {
                        Player* existingPlayer = players.getCurrentPlayer();
                        if (existingPlayer && existingPlayer->color() == color) {
                            colorTaken = true;
                            break;
                        }
                        players.next();
                    }
                }

                if (colorTaken) {
                    throw BadColor(name, colorChar);
                }
                colorValid = true;
            }
            catch (const BadColor& e) {
                e.print();
                cin.clear();
                cin.ignore(10000, '\n');
            }
            catch (const BadChoice& e) {
                cout << "Invalid color! Please choose from o,y,g,b: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }

        // If we get here, both name and color are valid
        players.addCell(name, color);
        break;
    }
}

void Game::takeTurn(Player* currentPlayer) {
    board.startTurn(currentPlayer);
    cout << "\nThe current board is:\n" << board << endl;
    cout << "Player " + currentPlayer->getName() + "'s turn.\n";

    bool keepRolling = true;
    while (keepRolling) {
        // Menu selection
        int choice;
        cout << "\nOptions: 1. Roll  2. Stop  3. Resign\nChoice: ";
        while (true) {
            try {
                if (!(cin >> choice)) {
                    cin.clear();
                    cin.ignore(10000, ' ');
                    throw BadChoice("Invalid input");
                }
                validMenu(choice);
                break;
            }
            catch (const BadChoice& e) {
                e.print();
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }

        if (choice == 2) { // Stop
            board.stop();
            cout << "\nTurn ended. Final positions:\n";
            board.print();
            keepRolling = false;
        }
        else if (choice == 1) { // Roll
            const int* dice = CSDice->roll();
            cout << "Dice rolled: a. " << dice[0] << " b. " << dice[1]
                 << " c. " << dice[2] << " d. " << dice[3] << endl;

            cout << "Choose first pair (e.g. AB): ";
            string selection;
            while (true) {
                try {
                    cin >> selection;
                    validDice(selection);
                    break;
                }
                catch (const BadSlot& e) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    e.print();
                }
                catch (const DuplicateSlot& e) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    e.print();
                }
            }

            char pair1 = toupper(selection[0]);
            char pair2 = toupper(selection[1]);
            int pairValues[2];

            pairValues[0] = dice[pair1-'A'] + dice[pair2-'A'];
            int total = dice[0] + dice[1] + dice[2] + dice[3];
            pairValues[1] = total - pairValues[0];

            int col1 = pairValues[0];
            int col2 = pairValues[1];

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
            } else {
                cout << "Current board (T = temporary):\n" << board << endl;

                if (move1 && board.getColumn(col1)->isCaptured()) {
                    currentPlayer->wonColumn(col1);
                    cout << "COLUMN " << col1 << " CAPTURED!\n";
                }
                if (move2 && board.getColumn(col2)->isCaptured()) {
                    currentPlayer->wonColumn(col2);
                    cout << "COLUMN " << col2 << " CAPTURED!\n";
                }

                if (currentPlayer->score() >= 3) {
                    cout << "PLAYER " << currentPlayer->getName() << " WINS!\n";
                    keepRolling = false;
                }
            }
        }
        else if (choice == 3) { // Resign
            cout << "\n" << currentPlayer->getName() << " resigns.\n";
            board.bust();

            cout << endl;
            players.init();
            players.remove();
            cout << endl;
            cout << "Number of players left: " << players.getCount() << endl;
            cout << endl;

            if (players.getCount() < 2) {
                cout << "Not enough players, ending the game!" << endl;
                cout << *players.getCurrentPlayer() << " WINS!\n";
                keepRolling = false;
                while (!players.empty()) {
                    players.remove();
                }
                return;
            }
        }
    }
}
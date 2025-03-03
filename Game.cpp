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

void Game::oneTurn(Player player) {
    board.startTurn(&player);  // Use the game's board instance

    while (true) {
        cout << "Pick a choice (Use the # associated with the choice): \n 1. roll  2. stop  3. resign" << endl;
        int choice;
        cin >> choice;

        if (choice == 2) { // Stop
            board.stop();
            for (int i = 0; i < 3; i++) {
                if (player.wonColumn(i)) {
                    cout << "Column " << i + 1 << " captured!" << endl;
                }
            }
            break;
        } else if (choice == 1) {
            Dice dice;
            const int* rollResults = dice.roll();
            cout << "Rolled Dice: ";
            for (int i = 0; i < 4; i++) {
                cout << rollResults[i] << " ";
            }
            cout << endl;

            char diceLabels[4] = {'A', 'B', 'C', 'D'};
            cout << "Choose a pair using letters (e.g., AC): ";
            char first, second;
            cin >> first >> second;

            int firstIndex = first - 'A';
            int secondIndex = second - 'A';

            if (firstIndex < 0 || firstIndex >= 4 || secondIndex < 0 || secondIndex >= 4 || firstIndex == secondIndex) {
                cout << "Invalid selection. Try again." << endl;
                continue;
            }

            int firstPair = rollResults[firstIndex] + rollResults[secondIndex];
            int remainingIndex1 = 0, remainingIndex2 = 0;

            for (int i = 0; i < 4; i++) {
                if (i != firstIndex && i != secondIndex) {
                    if (remainingIndex1 == 0) remainingIndex1 = i;
                    else remainingIndex2 = i;
                }
            }
            int secondPair = rollResults[remainingIndex1] + rollResults[remainingIndex2];

            bool move1 = board.move(firstPair);
            bool move2 = board.move(secondPair);
            board.print();

            if (!move1 && !move2) { // Bust condition
                cout << "Bust! No valid moves." << endl;
                board.bust();
                break;
            }
        } else {
            cout << "Invalid option. Try again." << endl;
        }
    }
}




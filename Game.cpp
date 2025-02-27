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
    fourDice(nullptr)
{
    Board board;
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

void oneTurn(Player& player) {
    Board board;
    board.startTurn(&player);

    while (true) {

        // cout << "Its " << player.getName(); Was going to have it so it said
        // who's turn it is
        cout << "Pick a choice (Use the # assosciated with the choice): \n 1. roll  2. stop    3. resign" << endl;
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
            
        }




}
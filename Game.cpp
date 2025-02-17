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
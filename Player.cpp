//======================================================
// Project: Player  File: Player.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Player.h"

// Constructor
Player::Player(const string playerName&, ECcolor playerColor)
    : playerName(playerName), playerColor(playerColor), colsCaptured(0), scoreboard() {}

Player::~Player() {}

// Print function
ostream& Player::print(ostream& os) {
    os << "Player Name: " << playerName << endl;
    os << "Color: " << ECcolorNames[(int)playerColor] << endl; // Use ECcolorNames array
    os << "Score: " << colsCaptured << endl;
    os << "Columns Captured: ";
    for (int y = 0; y < colsCaptured; ++y) {
        os << scoreboard[y] << " ";
    }
    os << endl;
    return os;
}

// Accessor for color
ECcolor Player::getColor() const {
    return playerColor;
}

// Accessor for score
int Player::getScore() const {
    return colsCaptured;
}

// Function to register a captured column

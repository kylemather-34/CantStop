//======================================================
// Project: Player  File: Player.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Player.h"

// Constructor
Player::Player(const string& playerName, ECcolor playerColor)
    : playerName(playerName), playerColor(playerColor), playerScore(0), scoreboard() {}

Player::~Player() = default;

// Print function
ostream& Player::print(ostream& os) {
    os << "Player Name: " << playerName << endl;
    os << "Color: " << ECcolorNames[static_cast<int>(playerColor)] << endl; // Use ECcolorNames array
    os << "Score: " << score << endl;
    os << "Columns Captured: ";
    for (int y = 0; y < playerScore; ++y) {
        os << scoreboard[y] << " ";
    }
    os << endl;
    return os;
}

// Accessor for color
ECcolor Player::color() const {
    return playerColor;
}

// Accessor for score
int Player::score() const {
    return playerScore;
}

// Function to register a captured column
bool Player::wonColumn(int colNum) {
    if (playerScore < 3) {
        scoreboard[playerScore] = colNum; // Store the column number
        ++playerScore; // Increment the score
        return playerScore == 3; // Return true if 3 columns are captured
    }
    return false;
}
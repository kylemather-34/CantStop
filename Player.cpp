//======================================================
// Project: Player  File: Player.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Player.hpp"

// Constructor: Initializes a Player object with a name, color,
// score set to 0, and an empty scoreboard
Player::Player(const string pName, ECcolor pColor)
    : pName(pName), pColor(pColor), pScore(0) {
        for (int &y : pScoreboard) y = 0; // Initialize scoreboard to 0
    }

// Destructor, uses default behavior
Player::~Player() = default;

// Function to print player details to the output stream
ostream& Player::print(ostream& os) const{
    os << "Player Name: " << pName << endl;
    os << "Color: " << ECcolorNames[(int)pColor] << endl;
    os << "Score: " << pScore << endl;
    os << "Columns Captured: ";
    for (int y = 0; y < pScore; ++y) { // Loop to test both logic points work for captured column
        os << pScoreboard[y] << " ";
    }
    os << endl;
    return os;
}

// Getter function retrieves player color
ECcolor Player::color() const {
    return pColor;
}

// Getter function retrieves player score
int Player::score() const {
    return pScore;
}

// Records a won column and updates the players score
bool Player::wonColumn(int colNum) {
    if (pScore < 3) { // Ensure only up to 3 columns are recorded
        pScoreboard[pScore] = colNum;
        ++pScore;
        return pScore == 3;
    }
    return false; // No change is already at max score
}

// Overloaded output stream operator to print Player details
ostream& operator<<(ostream& os, const Player& player) {
    return player.print(os);
}
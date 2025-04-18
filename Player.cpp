//======================================================
// Project: Can't Stop  File: Player.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Player.hpp"

// Constructor: Initializes a Player object with a name, color,
// score set to 0, and an empty scoreboard
Player::Player(const string playerName, ECcolor playerColor)
    : playerName(playerName), playerColor(playerColor), playerScore(0) {
        for (int &y : scoreboard) y = 0; // Initialize scoreboard to 0
    }

// Destructor, uses default behavior
Player::~Player() = default;

// Function to print player details to the output stream
ostream& Player::print(ostream& os) const{
    os << "Player Name: " << playerName << endl;
    os << "Color: " << ECcolorNames[(int)(playerColor)] << endl;
    os << "Score: " << playerScore << endl;
    os << "Columns Captured: ";
    for (int y = 0; y < playerScore; ++y) { // Loop to test both logic points work for captured column
        os << scoreboard[y] << " ";
    }
    os << endl;
    return os;
}

// Getter function retrieves player color
ECcolor Player::color() const {
    return playerColor;
}

// Getter function retrieves player score
int Player::score() const {
    return playerScore;
}

// Records a won column and updates the players score
bool Player::wonColumn(int colNum) {
    if (!hasWonColumn(colNum) && playerScore < 3) {
        scoreboard[playerScore] = colNum;
        ++playerScore;
        return playerScore == 3;
    }
    return false;
}

bool Player::hasWonColumn(int colNum) const {
    for (int i = 0; i < playerScore; ++i) {
        if (scoreboard[i] == colNum) return true;
    }
    return false;
}

// Overloaded output stream operator to print Player details
ostream& operator<<(ostream& os, const Player& player) {
    return player.print(os);
}
//======================================================
// Project: Player  File: Player.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Player.hpp"

// Constructor: Initializes a Player object with a name, color, and a cleared scoreboard
Player::Player(const string name, ECcolor color)
    : name(name), color(color) {
    for (int &y : scoreboard) y = 0; // Initialize scoreboard to 0
}

// Destructor, uses default behavior
Player::~Player() = default;

// Function to print player details in a single line
ostream& Player::print(ostream& os) const {
    os << name << " [" << ECcolorNames[static_cast<int>(color)]
       << "] Score: " << score << " Captured: ";
    for (int y = 0; y < score; ++y) {
        os << scoreboard[y] << " ";
    }
    return os;
}

// Records a won column and updates the player's score
bool Player::wonColumn(int colNum) {
    return (score < 3) ? (scoreboard[score++] = colNum, score == 3) : false;
}

// Overloaded output stream operator to print Player details
ostream& operator<<(ostream& os, const Player& player) {
    return player.print(os);
}
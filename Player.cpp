//======================================================
// Project: Player  File: Player.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Player.h"

Player::Player(const string playerName, ECcolor playerColor)
    : playerName(playerName), playerColor(playerColor), playerScore(0), scoreboard(){}

Player::~Player() = default;

ostream& Player::print(ostream& os) const{
    os << "Player Name: " << playerName << endl;
    os << "Color: " << ECcolorNames[static_cast<int>(playerColor)] << endl;
    os << "Score: " << playerScore << endl;
    os << "Columns Captured: ";
    for (int y = 0; y < playerScore; ++y) {
        os << scoreboard[y] << " ";
    }
    os << endl;
    return os;
}

ECcolor Player::color() const {
    return playerColor;
}

int Player::score() const {
    return playerScore;
}

bool Player::wonColumn(int colNum) {
    if (playerScore < 3) {
        scoreboard[playerScore] = colNum;
        ++playerScore;
        return playerScore == 3;
    }
    return false;
}

ostream& operator<<(ostream& os, const Player& player) {
    return player.print(os);
}
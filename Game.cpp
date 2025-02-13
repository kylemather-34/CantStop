//======================================================
// Project: Player  File: Game.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#include "Game.h"
#include "enums.hpp"

// Constructor
Game::Game() :
    cOne(2), cTwo(7),
    pOne(getNewPlayer()), pTwo(getNewPlayer())
{
    fourDice = new Dice(4);
}

Game::~Game() {
    delete[] fourDice; // Free allocated dice array
}

// Convert string to ECcolor
ECcolor stringToColor(const std::string& str) {
    for (size_t y = 0; y < static_cast<size_t>(ECcolor::Count); ++y) {
        if (ECcolorNames[y] == str) {
            return static_cast<ECcolor>(y);
        }
    }
    return ECcolor::error; // Default if not found
}

/* getNewPlayer function inputs player's data from keyboard
 * and calls the constructor */
Player Game::getNewPlayer() {
    string name, colorStr;
    ECcolor color;

    cout << "Enter player name: ";
    cin >> name;

    cout << "Enter player color (white, orange, yellow, green, blue): ";
    cin >> colorStr;

    color = stringToColor(colorStr); // Convert string input to ECcolor

    if (color == ECcolor::error) {
        cout << "Invalid color! Defaulting to white.\n";
        color = ECcolor::white;
    }

    return Player(name, color);
}

// Getter method for the dice array
Dice* Game::getDice() const {
    return fourDice;
}

// Getter method for Player One
Player& Game::getPlayerOne(){
    return pOne;
}

// Getter method for Player Two
Player& Game::getPlayerTwo(){
    return pTwo;
}

// Getter method for Column One
Column& Game::getColumnOne(){
    return cOne;
}

// Getter method for Column Two
Column& Game::getColumnTwo(){
    return cTwo;
}
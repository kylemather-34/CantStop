//======================================================
// Project: Player  File: Player.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#ifndef PLAYER_H
#define PLAYER_H
#include "tools.hpp"
#include "enums.h"
#include <string>
#include <array>

class Player {
    private:
        string playerName; // Player name, e.g. RedWolf or RubyMan
        ECcolor playerColor; // Player color from ECcolor enum
        int colsCaptured; // Number of columns captures
        array<int, 3> scoreboard; // Array of 3 integers for columns captured
    public:
        // Constructor
        Player(const string playerName&, ECcolor playerColor);

        // Destructor
        ~Player();

        // Print function
        ostream& print(ostream&);

        // Accessor for color
        ECcolor getColor() const;

        // Accessor for score
        int getScore() const;

        // Function to register a captured column
        bool wonColumn(int colNum);
};

// Overload the << operator for Player
inline ostream& operator<<(ostream& os,Player& player) {
    return player.print(os);
}
#endif //PLAYER_H

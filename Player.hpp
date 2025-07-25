//======================================================
// Project: Can't Stop  File: Player.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#ifndef PLAYER_H
#define PLAYER_H
#include "tools.hpp"
#include "enums.hpp"

class Player {
    private:
        string playerName;
        ECcolor playerColor;
        int playerScore;
        int scoreboard[3]{};
    public:
        explicit Player(const string playerName, ECcolor color);
        ~Player();
        void print() const;
        ostream& print(ostream&) const;
        ECcolor color() const;
        int score() const;
        bool wonColumn(int colNum);
        string getName() {return playerName;}
        bool hasWonColumn(int colNum) const;
};

ostream& operator<<(ostream&, const Player&);
#endif //PLAYER_H


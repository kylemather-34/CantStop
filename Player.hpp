//======================================================
// Project: Player  File: Player.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#ifndef PLAYER_H
#define PLAYER_H
#include "tools.hpp"
#include "enums.hpp"

class Player {
    private:
        string pName;
        ECcolor pColor;
        int pScore;
        int pScoreboard[3]{};
    public:
        explicit Player(const string pName, ECcolor color);
        ~Player();
        void print() const;
        ostream& print(ostream&) const;
        ECcolor color() const;
        int score() const;
        bool wonColumn(int colNum);
};

ostream& operator<<(ostream&, const Player&);
#endif //PLAYER_H


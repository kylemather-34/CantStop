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
        string name;
        ECcolor color;
        int score = 0;
        int scoreboard[3]{};
    public:
        explicit Player(const string name, ECcolor color);
        ~Player();
        void print() const;
        ostream& print(ostream&) const;
        ECcolor getColor() const {return color;}
        int getScore() const {return score;}
        bool wonColumn(int colNum);
};

ostream& operator<<(ostream&, const Player&);
#endif //PLAYER_H
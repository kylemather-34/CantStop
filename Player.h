//======================================================
// Project: Player  File: Player.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#ifndef PLAYER_H
#define PLAYER_H
#include "tools.hpp"
#include <string>

class Player {
    private:
      enum Ecolor { RED, BLUE, GREEN };

      string playerName;
      int columPlayerCaptured;
      int scoreboard {};
      ECOLOR color;
    public:
        Player(playerName, color);
        ~Player();
        ostream& print(ostream&);
        Ecolor getColor();








};
#endif //PLAYER_H

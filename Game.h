//======================================================
// Project: Can't Stop  File: Game.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#ifndef GAME_H
#define GAME_H
#include "Column.hpp"
#include "Dice.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "CList.h"
#include "tools.hpp"
#include "Tee.h"

class Game {
    private:
        Board board;
        Dice* fourDice;
        Column cOne;
        Column cTwo;
        CList players;

    public:
        Game();
        ~Game() {delete[] fourDice;}
        void addPlayer();
        void takeTurn (Player* player);
        Dice* getDice() const {return fourDice;}
        Column& getColumnOne() {return cOne;}
        Column& getColumnTwo() {return cTwo;}
};
#endif //GAME_H

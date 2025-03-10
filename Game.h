//======================================================
// Project: Player  Game.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#ifndef GAME_H
#define GAME_H
#include "Column.hpp"
#include "Dice.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "tools.hpp"

class Game {
    private:
        Board board;
        Game* game;
        Dice* fourDice;
        Player pOne;
        Player pTwo;
        Column cOne;
        Column cTwo;

    public:
        explicit Game();
        ~Game();
        Player getNewPlayer();
        void oneTurn (Player* player);
        Dice* getDice() const {return fourDice;}
        Player& getPlayerOne() {return pOne;}
        Player& getPlayerTwo() {return pTwo;}
        Column& getColumnOne() {return cOne;}
        Column& getColumnTwo() {return cTwo;}
};
#endif //GAME_H

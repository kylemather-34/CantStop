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

class Game {
private:
        CList players;
        Board board;
        Column cOne;
        Column cTwo;
        CantStopDice* CSDice;

        void checkData(const string& name, char colorChar);
        void validDice(const string &selection);
        void validMenu(const int& input);

public:
        Game();
        ~Game() {delete[] CSDice;}
        void addPlayer();
        void takeTurn (Player* player);
        Dice* getDice() const {return CSDice;}
        Column& getColumnOne() {return cOne;}
        Column& getColumnTwo() {return cTwo;}
};
#endif //GAME_H

//======================================================
// Project: Player  Game.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#ifndef GAME_H
#define GAME_H
#include "Column.hpp"
#include "Dice.hpp"
#include "Player.hpp"
#include "tools.hpp"

class Game {
    private:
        Dice* fourDice;
        Player pOne;
        Player pTwo;
        Column cOne;
        Column cTwo;

    public:
        explicit Game();
        ~Game();
        Player getNewPlayer();
        [[nodiscard]] Dice* getDice() const;
        [[nodiscard]] Player& getPlayerOne();
        [[nodiscard]] Player& getPlayerTwo();
        [[nodiscard]] Column& getColumnOne();
        [[nodiscard]] Column& getColumnTwo();
};
#endif //GAME_H

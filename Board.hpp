//
// Created by Kyle on 2/17/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include "Player.hpp"
#include "Column.hpp"
#include "tools.hpp"

class Board {
    private:
        int countTowers;
        int towerCols[3];
        Column* backBone[13];
        Player* currentPlayer;
    public:
        Board();
        ~Board();
        void print() const;
        void startTurn(Player* player);
        bool move(int column);
        void stop();
        void bust();
        Column* getColumn(int column);
};

ostream& operator<<(ostream& os, const Board& board);
#endif //BOARD_H

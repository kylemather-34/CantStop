//
// Created by Kyle on 2/17/2025.
//

#include "Board.h"

// Constructor
Board::Board() {
    countTowers = 0;
    for (int y = 0; y < 3; ++y) towerCols[y] = -1;

    //Initialized columns (positions 0 and 1 are unused)
    backBone[0] = backBone[1] = nullptr;
    for (int y = 2; y <= 12; ++y) {
        backBone[y] = new Column(y); // Delegate column size to Column constructor
    }
}

// Destructor cleans up allocated memory
Board::~Board() {
    for (int y = 2; y <= 12; ++y) {
        delete backBone[y];
    }
}

void Board::print() {
    for (int y = 2; y <= 12; ++y) {
        cout << "Column " << y << ": ";
        if (backBone[y]) backBone[y]->print();
        cout << endl;
    }
}

ostream& operator<<(std::ostream& os, const Board& board) {
    board.print();
    return os;
}
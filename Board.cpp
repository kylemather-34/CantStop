//======================================================
// Project: Can't Stop  File: Board.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#include "Board.hpp"

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

void Board::print() const {
    for (int y = 2; y <= 12; ++y) {
        cout << "Column " << y << ": ";
        if (backBone[y]) {
            backBone[y]->print(cout); // Delegate printing to the Column class
        } else {
            cout << "Invalid Column";
        }
        cout << endl;
    }
}

ostream& operator<<(ostream& os, const Board& board) {
    board.print();
    return os;
}

void Board::startTurn(Player* player) {
    currentPlayer = player;
    countTowers = 0;
    for (int y = 0; y < 3; ++y) towerCols[y] = -1;
}

bool Board::move(int column) {
    if (column < 2 || column > 12 || !backBone[column]) return false;

    // Check if the column is already captured
    if (backBone[column]->isCaptured()) return false;

    // Check if the column is pending for another player
    if (backBone[column]->isPending(currentPlayer)) return false;

    // Check if a tower is already in this column
    bool towerExists = false;
    for (int y = 0; y < countTowers; ++y) {
        if (towerCols[y] == column) {
            towerExists = true;
            break;
        }
    }

    // If no tower exists and all towers are in use, return false
    if (!towerExists && countTowers == 3) return false;

    // Place a new tower if necessary
    if (!towerExists) {
        // Attempt to start a tower for the current player
        if (!backBone[column]->startTower(currentPlayer)) {
            return false; // Tower couldn't be started, return false
        }
        towerCols[countTowers++] = column; // Tower placed
    }

    // Advance the tower in the column
    return backBone[column]->move();
}


// Stop function: finalizes tower positions
void Board::stop() {
    for (int i = 0; i < countTowers; ++i) {
        backBone[towerCols[i]]->stop(currentPlayer);
    }
    countTowers = 0;
}


// Bust function: removes all towers
void Board::bust() {
    for (int i = 0; i < countTowers; ++i) {
        backBone[towerCols[i]]->bust();
    }
    countTowers = 0;
}

Column* Board::getColumn(int column) {
    if (column < 2 || column > 12) return nullptr; // Ensure valid column range
    return backBone[column];
}
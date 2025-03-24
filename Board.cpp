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

    Column* col = backBone[column];

    // Check if column is captured by anyone
    if (col->isCaptured()) return false;

    // Check if current player already has progress here
    if (col->hasPlayerMarker(currentPlayer)) {
        return col->move(); // Advance existing marker
    }

    // Check tower limits
    if (countTowers >= 3) return false;

    // Start new tower
    if (col->startTower(currentPlayer)) {
        towerCols[countTowers++] = column;
        return true;
    }

    return false;
}



// Stop function: finalizes tower positions
void Board::stop() {
    for (int y = 0; y < countTowers; ++y) {
        backBone[towerCols[y]]->stop(currentPlayer);
    }
    countTowers = 0;
}


// Bust function: removes all towers
void Board::bust() {
    for (int y = 0; y < countTowers; ++y) {
        backBone[towerCols[y]]->bust();
    }
    countTowers = 0;
}

Column* Board::getColumn(int column) {
    if (column < 2 || column > 12) return nullptr; // Ensure valid column range
    return backBone[column];
}
//
// Created by Kyle on 2/17/2025.
//

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
        if (backBone[y]) backBone[y]->print(cout);
        cout << endl;
    }
}

ostream& operator<<(std::ostream& os, const Board& board) {
    board.print();
    return os;
}

void Board::startTurn(Player* player) {
    currentPlayer = player;
    countTowers = 0;
    for (int y = 2; y < 3; ++y) towerCols[y] = -1;
}

bool Board::move(int column) {
    if (column < 2 || column > 12 || !backBone[column]) return false;

    // Check if column is captured or pending
    if (backBone[column]->isCaptured() || backBone[column]->isPending(currentPlayer)) return false;

    // If column has no tower and there are no unused towers, return false
    bool towerExists = false;
    for (int i = 0; i < countTowers; ++i) {
        if (towerCols[i] == column) {
            towerExists = true;
            break;
        }
    }

    if (!towerExists && countTowers == 3) return false;

    // Place tower if possible
    if (!towerExists) {
        towerCols[countTowers++] = column;
    }

    backBone[column]->move();
    return true;
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
//======================================================
// Project: Can't Stop  File: Column.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Column.hpp"

Column::Column(int a) : columnNumber(a), colState(ColState::available){
    for (int &pos : markerPositions) {
        pos = 0;
    }
}

Column::~Column () = default;

string Column::colStateToString(ColState state) const {
    switch (state) {
        case ColState::captured: return "Captured";
        case ColState::pending: return "Pending";
        case ColState::available: return "Available";
    }
}

ostream &Column::print(ostream& os) const {
    string stateStr = colStateToString(colState);

    static const int columnHeights[13] = {0, 0, 3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3}; // Heights for columns 2-12

    int maxHeight = columnHeights[columnNumber]; // Get the correct height

    os << columnNumber << "  " << stateStr << "   ";

    for (int pos = maxHeight; pos >= 1; --pos) {
        string square = "------"; // Default empty slot

        if (markerPositions[(int)(ECcolor::white)] == pos) {
            square[0] = 'T';
        }

        for (int k = 1; k < (int)(ECcolor::Count); ++k) {
            if (markerPositions[k] == pos) {
                square[k + 1] = getColorChar((ECcolor)(k));
            }
        }

        os << square << "  ";
    }

    os << endl;
    return os;
}

// Helper function to get color character
char Column::getColorChar(ECcolor color) const {
    switch (color) {
        case ECcolor::white: return 'W';
        case ECcolor::orange: return 'O';
        case ECcolor::yellow: return 'Y';
        case ECcolor::green: return 'G';
        case ECcolor::blue: return 'B';
        default: return '-';
    }
}

bool Column::startTower(const Player *player) {
    ECcolor playerColor = (*player).color();

    int playerPos = (int)(playerColor);
    int towerPos = markerPositions[(int)(ECcolor::white)];
    if (towerPos > 0) { return false; }

    int newTowerPos;
    if (playerPos == 0) {
        newTowerPos = 1;
    } else {
        newTowerPos = playerPos + 1;
    }
    markerPositions[(int)(ECcolor::white)] = newTowerPos;

    if (newTowerPos >= 7) {
        colState = ColState::pending;
    }

   markerPositions[(int)(playerColor)] = newTowerPos;
   markerPositions[(int)(ECcolor::white)] = 0;

    return true;
}

bool Column::move() {
    int& towerPos = markerPositions[(int)(ECcolor::white)];
    towerPos++;
    if (towerPos >= 1) towerPos++;
    if (towerPos < 7) colState = ColState::pending;
    if (towerPos >= 7) colState = ColState::captured;
    return true;
}

void Column::stop(Player* player) {
    ECcolor playerColor = player->color();

    markerPositions[(int)(playerColor)] = markerPositions[(int)(ECcolor::white)];
    markerPositions[(int)(ECcolor::white)] = 0;  // Remove tower

    // If the column state is pending, change it to captured and call wonColumn()
    if (colState == ColState::pending) {
        colState = ColState::captured;
        player->wonColumn(columnNumber);
    }
}

bool Column::isCaptured() const {
    return colState == ColState::captured;
}

bool Column::isPending(const Player* player) const {
    return colState == ColState::pending;
}

void Column::bust() {
    for (int& pos : markerPositions) {
        pos = 0; // Reset all marker positions
    }
    colState = ColState::available; // Reset column state
}
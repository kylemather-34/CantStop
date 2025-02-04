//======================================================
// Project: Dice  File: Column.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Column.h"

Column::Column(int a) : columnNumber(a), colState(ColState::available){
    for (int &pos : markerPositions) {
        pos = 0;
    }
    if (a < 2 || a > 12) {
        throw out_of_range("Column number must be between 2 and 12.");
    }
}

Column::~Column () = default;

ColState Column::state() const {
    return colState;
}

ostream &Column::print(ostream& os) const {
    // Convert column state to a string
    std::string stateStr;
    switch (colState) {
        case ColState::captured: stateStr = "Captured"; break;
        case ColState::pending: stateStr = "Pending"; break;
        case ColState::available: default: stateStr = "Available"; break;
    }

    // Print column number and state
    std::cout << columnNumber << "  " << stateStr << "   ";

    // Print the column's marker positions
    for (int pos = 1; pos <= 7; ++pos) { // Assuming positions are between 1 and 7
        string square = "------"; // Default empty slots

        // Check for tower in this position
        if (markerPositions[static_cast<int>(ECcolor::white)] == pos) {
            square[0] = 'T'; // Tower is always stored in White's position
        }

        // Check for player markers in this position
        for (int i = 0; i < static_cast<int>(ECcolor::Count); ++i) {
            if (markerPositions[i] == pos) {
                square[i + 1] = getColorChar(static_cast<ECcolor>(i));
            }
        }

        os << square << "  ";
    }

    os << endl;
    return os;
}

// Helper function to get color character
char getColorChar(ECcolor color) {
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

    // Finds player position off of color
    int playerPos = static_cast<int>(playerColor);
    // Finds the current tower position
    int towerPos = markerPositions[static_cast<int>(ECcolor::orange)];
    // If current tower position is greater than 0, returns false
    if (towerPos > 0) { return false; }

    // If it gets passed that, we will continue with creating a new tower
    int newTowerPos;
    if (playerPos == 0) {
        newTowerPos = 1;
    } else {
        newTowerPos = playerPos + 1;
    }
    markerPositions[static_cast<int>(ECcolor::white)] = newTowerPos;

    if (newTowerPos >= 7) {
        colState = ColState::pending;
    }

    markerPositions[static_cast<int>(playerColor)] = newTowerPos;

    return true;
}

bool Column::move() {
/* Thinking about maybe making a variable that marks who is the current player.
 * That way when someone calls it we can make sure that the person calling it is the one that
 * just created the tower. That's if I am understanding that correctly.
 */
}

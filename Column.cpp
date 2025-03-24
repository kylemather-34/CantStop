//======================================================
// Project: Dice  File: Column.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Column.hpp"

Column::Column(int a) : columnNumber(a), colState(ColState::available){
    for (int &pos : markerPositions) {pos = 0;}
    if (a < 2 || a > 12) {
        throw out_of_range("Column number must be between 2 and 12.");
    }
}

Column::~Column () = default;

string Column::colStateToString(ColState state) const{
    switch (state) {
        case ColState::captured: return "Captured";
        case ColState::pending: return "Pending";
        case ColState::available: return "Available";
        default: return "Unknown";
    }
}

ostream &Column::print(ostream& os) const {
    // Convert column state to a string
    string stateStr;
    switch (colState) {
        case ColState::captured: stateStr = "Captured"; break;
        case ColState::pending: stateStr = "Pending"; break;
        case ColState::available: default: stateStr = "Available"; break;
    }

    static const int columnHeights[13] = {0, 0, 3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3}; // Heights for columns 2-12

    int maxHeight = columnHeights[columnNumber]; // Get the correct height

    os << columnNumber << "  " << stateStr << "   ";

    // Print the column's marker positions
    for (int pos = maxHeight; pos >= 1; --pos) {
        string square = "------"; // Default empty slot

        // Check for tower in this position
        /*if (markerPositions[(int)(ECcolor::white)] == pos) {
            square[0] = 'T'; // Tower is always stored in White's position
        }*/

        for (int i = 1; i < (int)(ECcolor::Count); ++i) {
            if (markerPositions[i] == pos) {
                square[0] = 'T';  // Tower should be in front of player markers
                break;  // Ensure only one 'T' is placed
            }
        }

        // Check for player markers in this position
        for (int y = 1; y < (int)(ECcolor::Count); ++y) {
            if (markerPositions[y] == pos) {
                square[y + 1] = getColorChar(static_cast<ECcolor>(y));
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

const int* Column::getMarkerPositions() const {
    return markerPositions;
}

bool Column::startTower(const Player *player) {
    ECcolor playerColor = (*player).color();

    // Finds player position off of color
    int playerPos = (int)(playerColor);
    // Finds the current tower position
    int towerPos = markerPositions[(int)(ECcolor::orange)];
    // If current tower position is greater than 0, returns false
    if (towerPos > 0) { return false; }

    // If it gets passed that, we will continue with creating a new tower
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

    // If tower isn't marked by players color, it will be here
   markerPositions[(int)(playerColor)] = newTowerPos;
   markerPositions[(int)(ECcolor::white)] = 0;

    return true;
}

bool Column::move() {
    int& towerPos = markerPositions[(int)(ECcolor::white)];

    // Check if there is a tower to move
    if (towerPos == 0) {
        // No tower exists, so place a new tower at position 1
        towerPos = 1;
    } else {
        // Advance the tower by one position
        towerPos++;
    }

    //Check if the column is pending
    if (towerPos != 0 && towerPos < 7) colState = ColState::pending;

    // Check if the column is captured
    if (towerPos >= 7) {
        colState = ColState::captured;
    }
    return true;
}

void Column::stop(Player* player) {
    // Get the player's color
    ECcolor playerColor = player->color();

    // Replace the tower with the player's color
    markerPositions[(int)(playerColor)] = markerPositions[(int)(ECcolor::white)];
    markerPositions[(int)(ECcolor::white)] = 0;  // Remove tower

    // If the column state is pending, change it to captured and call wonColumn()
    if (colState == ColState::pending) {
        colState = ColState::captured;
        player->wonColumn(columnNumber);  // Notify the player that they won the column
    }
}

bool Column::isCaptured() const {
    return colState == ColState::captured;
}

bool Column::isPending(const Player* player) const {
    return colState == ColState::pending;
}

void Column::bust() {
    for (int& pos : markerPositions) {pos = 0;}// Reset all marker positions
    colState = ColState::available; // Reset column state
}
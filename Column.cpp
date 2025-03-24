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

bool Column::startTower(const Player* player) {
    ECcolor playerColor = player->color();

    // If column is captured or already has this player's marker, fail
    if (isCaptured() || markerPositions[(int)playerColor] > 0) {
        return false;
    }

    // Start new tower at position 1
    markerPositions[(int)playerColor] = 1;
    colState = ColState::pending;
    return true;
}

bool Column::move() {
    // Find which player has a marker here
    int advancingPlayer = -1;
    for (int i = 1; i < (int)ECcolor::Count; i++) {
        if (markerPositions[i] > 0) {
            advancingPlayer = i;
            break;
        }
    }

    if (advancingPlayer == -1) return false;

    // Advance the marker
    int& currentPos = markerPositions[advancingPlayer];
    currentPos++;

    // Update column state
    static const int columnHeights[13] = {0, 0, 3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};
    if (currentPos >= columnHeights[columnNumber]) {
        colState = ColState::captured;
    }

    return true;
}

ostream& Column::print(ostream& os) const {
    os << "Column " << columnNumber << ": " << colStateToString(colState) << "   ";

    static const int columnHeights[13] = {0, 0, 3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};
    int maxHeight = columnHeights[columnNumber];

    for (int pos = 1; pos <= maxHeight; pos++) {
        bool markerFound = false;
        char marker = '-';

        // Check all player colors
        for (int color = 1; color < (int)ECcolor::Count; color++) {
            if (markerPositions[color] == pos) {
                marker = getColorChar(static_cast<ECcolor>(color));
                markerFound = true;
                break;
            }
        }

        // Print the square
        os << "--";
        if (markerFound) os << marker;
        else os << "-";
        os << "--";

        // Add space between squares
        if (pos < maxHeight) os << "  ";
    }

    return os;
}

void Column::stop(Player* player) {
    ECcolor playerColor = player->color();
    int towerPos = markerPositions[(int)ECcolor::white];

    if (towerPos > 0) {
        // Convert white marker to player's marker
        markerPositions[(int)playerColor] = towerPos;
        markerPositions[(int)ECcolor::white] = 0;

        // Check if column is captured
        static const int columnHeights[13] = {0, 0, 3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};
        if (towerPos >= columnHeights[columnNumber]) {
            colState = ColState::captured;
            player->wonColumn(columnNumber);
        }
    }
}



bool Column::isCaptured() const {
    return colState == ColState::captured;
}

bool Column::isPending(const Player* player) const {
    return colState == ColState::pending;
}

void Column::bust() {
    // Only clear white markers (temporary towers)
    markerPositions[(int)ECcolor::white] = 0;
    // Don't reset player markers or column state
}

bool Column::hasPlayerMarker(const Player* player) const {
    return markerPositions[(int)player->color()] > 0;
}
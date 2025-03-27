//======================================================
// Project: Dice  File: Column.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Column.hpp"

Column::Column(int a) : columnNumber(a), colState(ColState::available), isTemporary(false) {
    for (int& pos : markerPositions) {
        pos = 0; // Initialize all marker positions to 0
    }
    if (a < 2 || a > 12) {
        throw out_of_range("Column number must be between 2 and 12.");
    }
}

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



bool Column::startTower(const Player* player, bool temporary) {
    ECcolor playerColor = player->color();
    int colorIndex = (int)(playerColor);

    // Only reject if column is captured OR player has an active marker (position >= 1)
    if (colState == ColState::captured || markerPositions[colorIndex] >= 1) {
        return false;
    }

    markerPositions[colorIndex] = 1;  // Start at position 1 (first step)
    colState = ColState::pending;
    isTemporary = temporary;
    return true;
}

bool Column::move() {
    // Find which player has a tower here
    int activePlayer = -1;
    for (int i = 1; i < (int)(ECcolor::Count); i++) {
        if (markerPositions[i] > 0) {
            activePlayer = i;
            break;
        }
    }

    if (activePlayer == -1) return false;

    // Advance the tower
    markerPositions[activePlayer]++;

    // Check for column capture
    if (markerPositions[activePlayer] >= getColumnHeight()) {
        colState = ColState::captured;
    }

    return true;
}

ostream& Column::print(ostream& os) const {
    os << "Column " << columnNumber << ": " << colStateToString(colState) << "   ";

    int maxHeight = getColumnHeight();

    for (int pos = 1; pos <= maxHeight; pos++) {
        bool markerFound = false;
        char marker = '-';

        // Check all player colors
        for (int color = 1; color < (int)(ECcolor::Count); color++) {
            if (markerPositions[color] == pos) {
                marker = isTemporary ? 'T' : getColorChar(static_cast<ECcolor>(color));
                markerFound = true;
                break;
            }
        }

        os << "--";
        if (markerFound) os << marker;
        else os << "-";
        os << "--";

        if (pos < maxHeight) os << "  ";
    }

    return os << endl;
}

ostream& operator<<(ostream& os, const Column& col) {
    return col.print(os);
}

void Column::stop(Player* player) {
    makePermanent();
    ECcolor playerColor = player->color();
    int colorIndex = (int)(playerColor);

    if (markerPositions[colorIndex] >= getColumnHeight()) {
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
    if (isTemporary) {
        for (int i = 0; i < 5; i++) {
            markerPositions[i] = 0;
        }
        colState = ColState::available;
    }
    isTemporary = false;
}

bool Column::hasPlayerMarker(const Player* player) const {
    return markerPositions[(int)player->color()] > 0;
}

int Column::getColumnHeight() const {
    static const int columnHeights[13] = {0, 0, 3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};
    return columnHeights[columnNumber];
}
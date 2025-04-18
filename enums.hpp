//======================================================
// Project: Can't Stop  File: enums.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#ifndef ENUMS_H
#define ENUMS_H
#include "tools.hpp"

//Enum class to define colors used for various game purposes
enum class ECcolor {
    white, orange, yellow, green, blue, error, Count
};

enum class ColState {
    available, pending, captured, error
};

enum class GameStatus {
    begun, done, quit
};

enum class RollResult {
    CONTINUE, BUST, WIN
};

inline ECcolor charToColor(char c) {
    switch (tolower(c)) {
        case 'o': return ECcolor::orange;
        case 'y': return ECcolor::yellow;
        case 'g': return ECcolor::green;
        case 'b': return ECcolor::blue;
        default: return ECcolor::error;
    }
}

extern const string ColNames[];
extern const string ECcolorNames[];
#endif //ENUMS_H

//======================================================
// Project: Player  File: enums.h
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

extern const string ColNames[];
extern const string ECcolorNames[];
#endif //ENUMS_H

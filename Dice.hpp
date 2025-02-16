//======================================================
// Project: Dice  File: Dice.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#ifndef DICE_H
#define DICE_H
#include "tools.hpp"


class Dice {
    private:
        int nDice = 0; //# of dice in the set
        int* rVal; // Array we will store rolls in
    public:
        Dice() : Dice(6) {} // Default to 6-sided dice
        Dice(int n); // Constructing the class
        ~Dice(); // Destructor
        const int* roll(); // Function for "rolling" the dice
        ostream& print(ostream&) const; // Print function

};
ostream& operator<<(ostream&, const Dice&);
#endif //DICE_H

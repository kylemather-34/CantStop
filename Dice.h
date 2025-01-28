//======================================================
// Project: Dice  File: Dice.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#ifndef DICE_H
#define DICE_H
using namespace std;
#include <ostream>


class Dice {
    private:
        int nDice = 0; //# of dice in the set
    public:
        int* rVal; // Array we will store rolls in
        Dice(int n); // Constructing the class
        ~Dice(); // Destructor
        const int* roll(); // Function for "rolling" the dice
        ostream& print(ostream&); // Print function
};

inline ostream& operator <<(ostream&,Dice&) ;
#endif //DICE_H

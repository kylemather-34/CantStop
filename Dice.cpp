//======================================================
// Project: Dice  File: Dice.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Dice.h"

using namespace std;

//Constructor
Dice::Dice(int n) : nDice(n) {
    rVal = new int[nDice];

}

//Destructor
Dice::~Dice() {
    delete[] rVal;
}

// Generates a random number in the range of 1 to nDice and returns into array
const int* Dice::roll () {
    for (int x = 0; x < nDice; x++) {
        rVal[x] = (rand() % (nDice) + 1);
    }
    return rVal;
}

//Print function
ostream& Dice::print(ostream& os) {
    // Printing each value in rVal into designated area
    for (int y = 0; y < nDice; y++) {
        os << rVal[y] << " ";
    }
    return os;
}

//Output operator
ostream& operator <<(ostream& os, Dice& d) {
    return d.print(os);
}

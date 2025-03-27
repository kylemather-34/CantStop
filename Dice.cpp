//======================================================
// Project: Can't Stop  File: Dice.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Dice.hpp"

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
        rVal[x] = (rand() % (6) + 1);
    }
    return rVal;
}

//Print function
ostream& Dice::print(ostream& os) const {
    // Printing each value in rVal into designated area
    for (int y = 0; y < nDice; y++) {
        os << rVal[y] << " ";
    }
    return os;
}

const int* CantStopDice::roll() {
    const int* diceVals = Dice::roll();

    cout << "Dice rolled: ";
    for (int x = 0; x < 4; ++x) {
        cout << char('A' + x) << ": " << diceVals[x] << " ";
    }
    cout << endl;

    // Get player's choice (unchanged)
    char pair1, pair2;
    bool valid = false;
    while (!valid) {
        cout << "Choose first pair (e.g. AB): ";
        cin >> pair1 >> pair2;
        pair1 = toupper(pair1);
        pair2 = toupper(pair2);

        if (pair1 != pair2 && (pair1 >= 'A' && pair1 <= 'D')
                          && (pair2 >= 'A' && pair2 <= 'D')) {
            valid = true;
                          } else {
                              cout << "Invalid selection. Choose two different dice (A-D).\n";
                          }
    }
    // Calculate pairs (using public getDice())
    const int* vals = getDice();
    pairValues[0] = vals[pair1-'A'] + vals[pair2-'A'];
    pairValues[1] = vals[0] + vals[1] + vals[2] + vals[3] - pairValues[0];

    return pairValues;
}

FakeDice::FakeDice() {
    diceFile.open(FAKE_DICE_FILE);
    if (!diceFile) {
        fatal("Could not open fake dice file: " FAKE_DICE_FILE);
    }
}

bool FakeDice::readNextRoll(int* values) {
    string line;
    if (!getline(diceFile, line)) return false;

    istringstream iss(line);
    for (int i = 0; i < 4; i++) {
        if (!(iss >> values[i])) return false;
    }
    return true;
}

const int* FakeDice::roll() {
    int values[4];
    if (!readNextRoll(values)) {
        fatal("End of fake dice file reached");
    }

    // Create a new array with the fake values
    int* fakeRolls = new int[4];
    for (int i = 0; i < 4; i++) {
        fakeRolls[i] = values[i];
    }

    // Store in our pairValues array (inherited from CantStopDice)
    myPairValues[0] = fakeRolls[0] + fakeRolls[1];
    myPairValues[1] = fakeRolls[2] + fakeRolls[3];

    delete[] fakeRolls;  // Clean up temporary array
    return myPairValues;
}

//Output operator
ostream& operator<<(ostream& os, const Dice& d) {
    return d.print(os);
}

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
    // Get the actual dice values from FakeDice
    const int* diceVals = fakeDice->roll();

    // Copy to our storage
    int* diceValues = new int[4];
    for (int x = 0; x < 4; x++) {
        diceValues[x] = diceVals[x];
    }

    // Display dice values
    cout << "Dice rolled: ";
    for (int x = 0; x < 4; ++x) {
        cout << char('A' + x) << ": " << diceValues[x] << " ";
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

    pairValues[0] = diceValues[pair1-'A'] + diceValues[pair2-'A'];

    int total = diceValues[0] + diceValues[1] + diceValues[2] + diceValues[3];
    pairValues[1] = total - pairValues[0];

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
    if (!getline(diceFile, line)) {
        return false;
    }

    istringstream iss(line);
    for (int x = 0; x < 4; x++) {
        if (!(iss >> values[x])) {
            values[x] = 1;  // Default value
        }
    }
    return true;
}

const int* FakeDice::roll() {
    int values[4];
    if (!readNextRoll(values)) {
        diceFile.clear();
        diceFile.seekg(0);
        if (!readNextRoll(values)) {
            fatal("Failed to read fake dice values");
        }
    }

    int *diceValues = new int[4];
    for (int x = 0; x < 4; x++) {
        diceValues[x] = values[x];
    }

    myPairValues[0] = diceValues[0] + diceValues[1];
    myPairValues[1] = diceValues[2] + diceValues[3];

    return diceValues;
}

//Output operator
ostream& operator<<(ostream& os, const Dice& d) {
    return d.print(os);
}

//======================================================
// Project: Can't Stop  File: Dice.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#ifndef DICE_H
#define DICE_H
#include "tools.hpp"
#define FAKE_DICE_FILE "fakedice.txt"
#include "Exceptions.h"

class Dice {
private:
    int nDice = 0; //# of dice in the set
    int* rVal; // Array we will store rolls in
public:
    Dice() : Dice(6){} // Default to 6-sided dice
    Dice(int n); // Constructing the class
    virtual ~Dice(); // Destructor
    virtual const int* roll(); // Function for "rolling" the dice
    const int* getDice() const { return rVal; }
    ostream& print(ostream&) const; // Print function
    void validDice(const string &selection);
};

class FakeDice : public Dice {
private:
    ifstream diceFile;
    int myPairValues[2];
    bool readNextRoll(int* values);
public:
    FakeDice();
    virtual ~FakeDice() {if (diceFile.is_open()) fatal("File could not be opened.");}
    const int* roll() override;
};

class CantStopDice : public Dice{
private:
    FakeDice* fakeDice;
    int pairValues[2];
public:
    CantStopDice() : Dice(4) {
        fakeDice = new FakeDice;
    }
    virtual ~CantStopDice() = default;
    const int* roll() override;
};

ostream& operator<<(ostream&, const Dice&);
#endif //DICE_H

//======================================================
// Project: Can't Stop  File: Exceptions.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "enums.hpp"

class BadPlayer {
private:
    string name;
    char colorChar;
public:
    BadPlayer(const string& n, char c) : name(n), colorChar(c) {}
    virtual ~BadPlayer() = default;
    virtual void print() const {
        cerr << "Invalid player input. Both name '" << name << "' and color '" << colorChar << "' are already in use.\n";
    }
    void basePrint() const {
        cerr << "Input received - Name: " << name << ", Color: " << colorChar << "\n";
    }
    string getName() const {return name;}
    char getColorChar() const {return colorChar;}
};

// Derived exception for bad name
class BadName : public BadPlayer {
public:
    BadName(const string& n, char c) : BadPlayer(n, c) {}
    void print() const override {
        cerr << "\nPlayer name '" << getName() << "' is already in use." << endl;
        basePrint();
    }
};

class BadColor : public BadPlayer {
public:
    BadColor(const string& n, char c) : BadPlayer(n, c) {}
    void print() const override {
        cerr << "\nColor '" << getColorChar() << "' is already taken by another player." << endl;;
    }
};

class BadChoice {
private:
    string choice;
public:
    BadChoice(const string& c) : choice(c) {}
    virtual ~BadChoice() = default;
    virtual void print() const {
        cerr << "Invalid choice: " << choice << "\n";
    }
    string getChoice() const { return choice; }
};

// Derived exception for duplicate slot selection
class DuplicateSlot : public BadChoice {
public:
    DuplicateSlot(const string& c) : BadChoice(c) {}
    void print() const override {
        cerr << "Error: You selected the same dice twice (" << BadChoice::getChoice() << ").\n";
    }
};

// Derived exception for bad slot selection
class BadSlot : public BadChoice {
public:
    BadSlot(const string& c) : BadChoice(c) {}
    void print() const override {
        cerr << "Error: Invalid dice selection (" << BadChoice::getChoice() << ").\n";
    }
};

#endif //EXCEPTIONS_H

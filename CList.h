//======================================================
// Project: Can't Stop  File: CList.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#ifndef CLIST_H
#define CLIST_H

#include "tools.hpp"
#include "Player.hpp"
#include <memory>

// Foward declaration of CList class
class CList;

// Cell class - servant class for CList
class Cell {
private:
    unique_ptr<Player> upp; // Unique ptr to hold Player data
    Cell* next; // Pointer to the next Cell in the circular list

    // Constructor
    Cell(unique_ptr<Player> player, Cell* nextCell = nullptr);

    // Destructor
    ~Cell(){cout << "Cell Destroyed";};

    // Friend declaration to allow CList access to private members
    friend class CList;
};

class CList {
private:
    int count; // Counter for number of Cells in list
    Cell* head; // Points to first Cell in list
    Cell* tail; // Points to last Cell in list
    Cell* current; // Points to current Cell
public:
    // Constructor
    CList();

    // Destructor
    ~CList();

    void clear();

    // Accessor function to return number of Cells in list
    int getCount() const {return count;};

    // Function to check if list is empty
    bool empty() const {return count == 0;};

    // Function to print all Cells in the list
    ostream& print(ostream& os) const;

    void print() const;

    Player* getCurrentPlayer() {
        if (current) {
            return current->upp.get();  // Access the Player via the unique_ptr
        }
        return nullptr;  // Return nullptr if no current Cell
    }
    // Add a new cell to the list
    void addCell(const string &name, ECcolor playerColor);

    // Initialize the current pointer to head of list
    void init();

    // Move current pointer to next cell and return its upp
    Cell* next();

    // Remove current cell and corresponding upp, delete both from list
    void remove();
    friend class Cell;
};

ostream& operator<<(ostream& os, const CList&);
#endif //CLIST_H

//======================================================
// Project: Can't Stop  File: CList.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#ifndef CLIST_H
#define CLIST_H

#include "tools.hpp"
#include "Player.hpp"
#include <memory>
class CList;

class Cell {
private:
    unique_ptr<Player> upp;
    Cell* next;
    Cell(unique_ptr<Player> player, Cell* nextCell = nullptr);
    ~Cell(){cout << "Cell Destroyed";};

    friend class CList;
};

class CList {
private:
    int count;
    Cell* head;
    Cell* tail;
    Cell* current;
public:
    CList();
    ~CList();
    int getCount() const {return count;};
    bool empty() const {return count == 0;};
    ostream& print(ostream& os) const;
    void print() const;
    Player* getCurrentPlayer() {
        if (current) {
            return current->upp.get();  // Access the Player via the unique_ptr
        }
        return nullptr;  // Return nullptr if no current Cell
    }
    void addCell(const string &name, ECcolor playerColor);
    void init();
    Cell* next();
    void remove();
    friend class Cell;
};

ostream& operator<<(ostream& os, const CList&);
#endif //CLIST_H

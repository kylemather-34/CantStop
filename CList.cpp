//======================================================
// Project: Player  File: CList.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#include "CList.h"

ofstream outFile("Output.txt", ios::app);

// Cell class implementation
Cell::Cell(unique_ptr<Player> player, Cell* nextCell)
    : upp(move(player)), next(nextCell) {}

Cell::~Cell() {
    cout << "Cell destroyed." << endl;
}

// CList class implementation
CList::CList() : count(0), head(nullptr), tail(nullptr), current(nullptr) {}

CList::~CList() {
    while (head) {
        remove();
    }
}

int CList::getCount() const {
    return count;
}

bool CList::empty() const {
    return count == 0;
}

void CList::print() const {
    if (empty()) {
        cout << "Empty list." << endl;
        return;
    }

    Cell* temp = head;
    do {
        temp->upp->print(outFile);
        temp = temp->next;
    } while (temp != head);
}

void CList::addCell(Cell* it) {
    if (empty()) {
        // Special case: first insertion
        head = it;
        head->next = head; // References itself
        tail = head; // Maintain tail pointer
    } else {
        // Insert at the end of the list
        it->next = head;
        tail->next = it;
        tail = it; // Maintain tail pointer
    }

    count++; // update count
}

void CList::init() {
    current = head;
}

Cell* CList::next() {
    if (empty()) {
        cout << "List is empty. No next player." << endl;
        return nullptr;
    }

    Cell* result = current; // Return the current Cell
    current = current->next; // Move to next Cell
    return result;
}

void CList::remove() {
    if (empty()) {
        cout << "List is empty. Nothing to remove." << endl;
        return;
    }

    Cell* temp = current;

    if (current == head) {
        // Special case: removing the head
        head = head -> next;
        tail->next = head; // Update tail's predecessor
    }

    current = current->next; // Move current to the next Cell
    delete temp; // Delete temp Cell
    count--; // Update count

    if (empty()) {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }
}
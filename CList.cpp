//======================================================
// Project: Can't Stop  File: CList.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#include "CList.h"

ofstream outFile("Output.txt", ios::app);

// Cell class implementation
Cell::Cell(unique_ptr<Player> player, Cell* nextCell)
    : upp(move(player)), next(nextCell) {}

// CList class implementation
CList::CList() : count(0), head(nullptr), tail(nullptr), current(nullptr) {}

CList::~CList() {
    while (head) {
        remove();
    }
}

void CList::clear() {
    while (head != nullptr) {
        remove();
    }
}
ostream& CList::print(ostream& os) const {
    if (empty()) {
        os << "Empty list." << endl;
        return os;
    }

    Cell* temp = head;
    do {
        os << "Player: " << temp->upp->getName() <<"("<< ECcolorNames[(int)(temp->upp->color())] << ")" << endl;
        temp = temp->next;
    } while (temp != head);

    return os;
}

void CList::addCell(const string& name, ECcolor playerColor) {
    unique_ptr<Player> player = make_unique<Player>(name, playerColor);
    Cell* it = new Cell(std::move(player), nullptr); // Use std::move to transfer ownership

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

    count++; // Update count
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
        if (head == tail) {
            // Case when there's only one element in the list
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            tail->next = head; // Update tail's predecessor to point to new head
        }
    } else if (current == tail) {
        // Special case: removing the tail
        Cell* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }
        tail = temp;
        tail->next = head; // Update tail's next to point to the head
    } else {
        // Regular case: removing a middle node
        Cell* prev = head;
        while (prev->next != current) {
            prev = prev->next;
        }
        prev->next = current->next; // Skip the current node
    }

    // Move current to the next Cell before deleting the current one
    current = current->next;

    delete temp; // Delete the current Cell
    count--; // Update count

    if (empty()) {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }
}

ostream& operator<<(ostream& os, const CList& CList) {
    return CList.print(os);
}

//======================================================
// Project: Dice  File: Column.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#ifndef COLUMN_H
#define COLUMN_H

#include "enums.hpp"
#include "Player.hpp"
#include "tools.hpp"

class Column {
    private:
        static int columnLength[13];
        const int columnNumber;
        ColState colState;
        int markerPositions[static_cast<int>(ECcolor::Count)]{};
    public:
        Column(int a);
        ~Column();
        [[nodiscard]] ColState state() const;
        string colStateToString(ColState state);
        ostream& print(ostream& os) const;
        [[nodiscard]] char getColorChar(ECcolor color) const;
        [[nodiscard]] const int* getMarkerPositions() const;
        bool startTower(const Player* player);
        bool move();
        void stop(Player* player);
        void bust();
};


ostream& operator<<(ostream&, const Column&);
#endif //COLUMN_H

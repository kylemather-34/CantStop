    //======================================================
    // Project: Can't Stop  File: Column.hpp
    // Author: Ryan Lang and Kyle Mather     Copyright: 2025
    //======================================================
    #ifndef COLUMN_H
    #define COLUMN_H

    #include "enums.hpp"
    #include "Player.hpp"
    #include "tools.hpp"

    class Column {
private:

    static int columnLength[11];
    const int columnNumber;
    ColState colState;
    int markerPositions[(int)ECcolor::Count]{};
        bool isTemporary = false;

public:
    Column(int a);
    ~Column();
    ColState state() const {return colState;}
    string colStateToString(ColState state) const;
        ostream& print(ostream& os) const;
        friend ostream& operator<<(ostream& os, const Column& col);
    char getColorChar(ECcolor color) const;
    const int *getMarkerPositions() const;
    bool startTower(const Player *player, bool temporary);
    bool move();
    void stop(Player* player);
    void capture(Player* player);
    bool isCaptured() const;
    bool isPending(const Player* player) const;
    void bust();
    bool hasPlayerMarker(const Player *player) const;

    void makePermanent();

    int getColumnHeight() const;
    };



#endif //COLUMN_H

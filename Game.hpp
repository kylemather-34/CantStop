//======================================================
// Project: Can't Stop  File: Game.h
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#ifndef GAME_H
#define GAME_H
#include "Column.hpp"
#include "Dice.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "CList.hpp"
#include "tools.hpp"

class Game {
protected:
        CList players;
        Board board;
        Column cOne;
        Column cTwo;
        CantStopDice* CSDice;
        GameStatus state;

        void initializePlayers();
        void validDice(const string& selection);
        void validMenu(const int& input);
        void addPlayer();
        string promptValidName();
        ECcolor promptValidColor(const string& name);
        bool isNameTaken(const string& name);
        bool isColorTaken(ECcolor color);
        int getMenuChoice();
        bool handleStop(Player* currentPlayer);
        bool handleRoll(Player* currentPlayer);
        const string getValidDiceSelection();
        void getDicePairs(const int* dice, const string& selection, int pairValues[2]);
        bool processMoves(Player* currentPlayer, int pairValues[2]);
        void checkCapturedColumns(Player* currentPlayer, int col1, int col2);
        GameStatus handleResign(Player* currentPlayer);
        void printDicePrompt();
        bool isColorCharValid(char c);
        bool operator==(GameStatus s) const;

public:
        Game();
        ~Game() { delete CSDice; }
        void play();
        GameStatus oneTurn(Player*);
};
#endif //GAME_H

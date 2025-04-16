//======================================================
// Project: Can't Stop  File: Game.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================

#include "Game.h"
#include "enums.hpp"
#include "tools.hpp"
#include "Exceptions.h"
#include <cstring>
#include <thread>

Game::Game() :
    cOne(2), cTwo(7), CSDice(nullptr), board(), state(GameStatus::begun)
{
    CSDice = new CantStopDice();
    initializePlayers();
    players.init();
}

void Game::initializePlayers() {
    int numOfPlayers;
    cout << "Please input your number of players (2-4): ";
    while (!(cin >> numOfPlayers) || numOfPlayers < 2 || numOfPlayers > 4) {
        cout << "Invalid input. Please enter a number between 2 and 4: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    for (int x = 0; x < numOfPlayers; x++) addPlayer();
}

void Game::validDice(const string& selection) {
    const char* validChoices = "abcdABCD";
    if (selection.length() != 2) throw BadSlot(selection);
    char first = tolower(selection[0]), second = tolower(selection[1]);
    if (!strchr(validChoices, first) || !strchr(validChoices, second)) throw BadSlot(selection);
    if (first == second) throw DuplicateSlot(selection);
}

void Game::validMenu(const int& input) {
    if (input < 1 || input > 3) throw BadChoice(to_string(input));
}

void Game::addPlayer() {
    string name;
    ECcolor color;
    while (true) {
        name = promptValidName();
        color = promptValidColor(name);
        players.addCell(name, color);
        break;
    }
}

string Game::promptValidName() {
    string name;
    while (true) {
        try {
            cout << "Enter player name: ";
            if (!(cin >> name)) throw BadChoice("Invalid name input");
            cin.ignore(10000, '\n');
            if (isNameTaken(name)) throw BadName(name, ' ');
            return name;
        } catch (const BadName& e) {
            e.print(); cin.clear(); cin.ignore(10000, '\n');
        } catch (const BadChoice& e) {
            cout << "Invalid name format. Please try again.\n";
            cin.clear(); cin.ignore(10000, '\n');
        }
    }
}

ECcolor Game::promptValidColor(const string& name) {
    char colorChar;
    cout << "Enter letter of color (o. orange, y. yellow, g. green, b. blue): ";
    while (true) {
        try {
            if (!(cin >> colorChar)) throw BadChoice("Invalid color input");
            colorChar = tolower(colorChar);
            if (!isColorCharValid(colorChar)) throw BadChoice("Invalid color letter");
            ECcolor color = charToColor(colorChar);
            if (isColorTaken(color)) throw BadColor(name, colorChar);
            return color;
        } catch (const BadColor& e) {
            e.print();
        } catch (const BadChoice& e) {
            cout << "Invalid color! Please choose from o,y,g,b: ";
        }
        cin.clear();                // Flush input stream
        cin.ignore(10000, '\n');    // Consume the rest of the line
    }
}

bool Game::isColorCharValid(char c) {
    c = tolower(c);
    return c == 'o' || c == 'y' || c == 'g' || c == 'b';
}

bool Game::isNameTaken(const string& name) {
    players.init();
    for (int x = 0; x < players.getCount(); x++) {
        string existing = players.getCurrentPlayer()->getName();
        transform(existing.begin(), existing.end(), existing.begin(), ::tolower);
        string input = name;
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (existing == input) return true;
        players.next();
    }
    return false;
}

bool Game::isColorTaken(ECcolor color) {
    players.init();
    for (int x = 0; x < players.getCount(); x++) {
        if (players.getCurrentPlayer()->color() == color) return true;
        players.next();
    }
    return false;
}

void Game::printDicePrompt() {
    cout << "Choose first pair (e.g. AB): ";
}

void Game::play() {
    while (state == GameStatus::begun) {
        if (players.getCount() == 0) {
            state = GameStatus::quit;
            break;
        }
        Player* currentPlayer = players.getCurrentPlayer();
        if (!currentPlayer) break;
        state = oneTurn(currentPlayer);
        if (state == GameStatus::begun) players.next();
    }
}

GameStatus Game::oneTurn(Player* currentPlayer) {
    board.startTurn(currentPlayer);
    cout << "\nThe current board is:\n" << board << endl;
    cout << "Player " + currentPlayer->getName() + "'s turn.\n";
    while (true) {
        int choice = getMenuChoice();
        if (choice == 1) {
            if (handleRoll(currentPlayer)) return GameStatus::done;
        } else if (choice == 2) {
            if (handleStop(currentPlayer)) return GameStatus::done;
            return GameStatus::begun;
        } else if (choice == 3) {
            return handleResign(currentPlayer);
        }
    }
}

int Game::getMenuChoice() {
    int choice;
    cout << "\nOptions: 1. Roll  2. Stop  3. Resign\nChoice: ";
    while (true) {
        try {
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(10000, ' ');
                throw BadChoice("Invalid input");
            }
            validMenu(choice);
            return choice;
        } catch (const BadChoice& e) {
            e.print(); cin.clear(); cin.ignore(10000, '\n');
        }
    }
}

bool Game::handleStop(Player* currentPlayer) {
    board.stop();
    for (int x = 0; x < 13; ++x) {
        Column* col = board.getColumn(x);
        if (col && col->isCaptured()) currentPlayer->wonColumn(x);
    }
    cout << "\nTurn ended.\n";
    return currentPlayer->score() >= 3;
}

bool Game::handleRoll(Player* currentPlayer) {
    const int* dice = CSDice->roll();
    cout << "Dice rolled: a. " << dice[0] << " b. " << dice[1]
         << " c. " << dice[2] << " d. " << dice[3] << endl;
    printDicePrompt();
    string selection = getValidDiceSelection();
    int pairValues[2];
    getDicePairs(dice, selection, pairValues);
    return processMoves(currentPlayer, pairValues);
}

string Game::getValidDiceSelection() {
    string selection;
    while (true) {
        try {
            cin >> selection;
            validDice(selection);
            return selection;
        } catch (const BadSlot& e) {
            cin.clear(); cin.ignore(10000, '\n'); e.print();
        } catch (const DuplicateSlot& e) {
            cin.clear(); cin.ignore(10000, '\n'); e.print();
        }
    }
}

void Game::getDicePairs(const int* dice, const string& selection, int pairValues[2]) {
    char pair1 = toupper(selection[0]), pair2 = toupper(selection[1]);
    pairValues[0] = dice[pair1 - 'A'] + dice[pair2 - 'A'];
    int total = dice[0] + dice[1] + dice[2] + dice[3];
    pairValues[1] = total - pairValues[0];
}

bool Game::processMoves(Player* currentPlayer, int pairValues[2]) {
    int col1 = pairValues[0], col2 = pairValues[1];
    bool move1 = board.move(col1), move2 = board.move(col2);
    cout << "\nAttempting moves: " << col1 << " and " << col2 << endl;
    cout << "Move " << col1 << ": " << (move1 ? "Success" : "Failed") << endl;
    cout << "Move " << col2 << ": " << (move2 ? "Success" : "Failed") << endl;
    if (!move1 && !move2) {
        cout << "BUST! No valid moves.\n";
        board.bust();
        cout << "Current board:\n" << board << endl;
        return false;
    }
    cout << "Current board (T = temporary):\n" << board << endl;
    checkCapturedColumns(currentPlayer, col1, col2);
    return currentPlayer->score() >= 3;
}

void Game::checkCapturedColumns(Player* currentPlayer, int col1, int col2) {
    if (board.getColumn(col1)->isCaptured()) {
        currentPlayer->wonColumn(col1);
        cout << "COLUMN " << col1 << " CAPTURED!\n";
    }
    if (board.getColumn(col2)->isCaptured()) {
        currentPlayer->wonColumn(col2);
        cout << "COLUMN " << col2 << " CAPTURED!\n";
    }
}

GameStatus Game::handleResign(Player* currentPlayer) {
    cout << "\n" << currentPlayer->getName() << " resigns.\n";
    board.bust();
    players.remove();
    if (players.getCount() == 1) {
        cout << "\nNot enough players, ending the game!\n";
        players.init();
        Player* remaining = players.getCurrentPlayer();
        if (remaining) {
            cout << "PLAYER " << remaining->getName() << " WINS!\n";
        }
        return GameStatus::quit;
    }
    cout << "\nNumber of players left: " << players.getCount() << endl;
    return GameStatus::begun;
}
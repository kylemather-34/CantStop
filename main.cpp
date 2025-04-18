//======================================================
// Project: Can't Stop  File: main.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "tools.hpp"
#include "unitTests.hpp"
#include "Game.hpp"
#include "Player.hpp"


int main(int argc, char* argv[]) {
    srand(time(nullptr));

    Game game1;
    game1.play();

    bye();  //Designates program termination

    return 0;
}
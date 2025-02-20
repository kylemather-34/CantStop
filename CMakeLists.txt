cmake_minimum_required(VERSION 3.30)
project(AdvanceC__)

set(CMAKE_CXX_STANDARD 20)

add_executable(AdvanceC__ main.cpp
        Dice.hpp
        Dice.cpp
        Player.hpp
        Player.cpp
        enums.hpp
        enums.cpp
        unitTests.hpp
        unitTests.cpp
        tools.cpp
        Column.hpp
        Column.cpp
        Game.h
        Game.cpp
        Board.hpp
        Board.cpp
)

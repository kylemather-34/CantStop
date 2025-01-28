cmake_minimum_required(VERSION 3.30)
project(AdvanceC__)

set(CMAKE_CXX_STANDARD 20)

add_executable(AdvanceC__ main.cpp
        Dice.h
        Dice.cpp
        Player.h
        Player.cpp)

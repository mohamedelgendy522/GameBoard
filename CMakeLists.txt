cmake_minimum_required(VERSION 3.29)
project(BoardGameFramework)

set(CMAKE_CXX_STANDARD 17)

add_executable(BoardGameFramework
        menu.cpp
        Big_XO_Tic_Tac_Toe.cpp
        Diamond_Tic_Tac_Toe.cpp
        Four_In_Row.cpp
        Infinity.cpp
        Memory_Tic_Tac_Toe.cpp
        Misere_Tic_Tac_Toe.cpp
        Numerical_Tic_Tac_Toe.cpp
        Obstacles_Tic_Tac_Toe.cpp
        Pyramid.cpp
        Shift_X_O.cpp
        SUS.cpp
        Ultimate.cpp
        Word_tic_tac_toe.cpp
        XO_Classes.cpp
)

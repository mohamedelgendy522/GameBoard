/**
 * @file XO_Demo.cpp
 * @brief Entry point for the FCAI X-O (Tic-Tac-Toe) game.
 *
 * This file initializes the X-O game by creating the user interface, board, and players.
 * It then launches the game loop via the GameManager class.
 * All dynamically allocated objects are properly deleted at the end.
 */

#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr

#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "Numerical.h"
using namespace std;

/**
 * @brief Main function to run the X-O game.
 *
 * This function orchestrates the game by:
 * - Initializing the random number generator
 * - Creating the X-O specific UI and board
 * - Setting up players using the UI
 * - Running the main game loop through the GameManager
 * - Performing cleanup of dynamically allocated memory
 *
 * @return int Returns 0 on successful execution.
 */
int main() {
/*
X0 game
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    UI<char>* game_ui = new XO_UI();

    Board<char>* xo_board = new X_O_Board();

    Player<char>** players = game_ui->setup_players();

    GameManager<char> x_o_game(xo_board, players, game_ui);

    x_o_game.run();

    delete xo_board;

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
*/
    // NUMERICAL GAME
    srand(static_cast<unsigned int>(time(0)));

    UI<int>* game_ui = new Numerical_UI();

    Board<int>* board = new Numerical();

    Player<int>** players = game_ui->setup_players();

    GameManager<int> game(board, players, game_ui);
    game.run();

    delete board;

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    delete[] players;

    return 0;
}

// =====================================================================
//    SUS_Game.cpp
//  Numeri

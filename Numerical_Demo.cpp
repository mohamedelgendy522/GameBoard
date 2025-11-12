
#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr

#include "BoardGame_Classes.h"
#include "Numerical_Tic_Tac_Toe.h"
using namespace std;

int main() {

    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    // Create an instance of the specific UI for X-O using a pointer 
    UI<int>* game_ui = new Numerical_UI();

    // Create the game board. For X-O, this is an X_O_Board.
    Board<int>* nxo_board = new Numerical_Board();

    // Use the UI to set up the players for the game.
    // The UI returns a dynamically allocated array of Player pointers.
    Player<int>** players = game_ui->setup_players();

    // Create the game manager with the board and the array of players.
    GameManager<int> Numerical_game(nxo_board, players, game_ui);

    // Run the game loop.
    Numerical_game.run();

    // --- Cleanup ---
    // Delete the dynamically allocated board object.
    delete nxo_board;

    // Delete the individual player objects.
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    // Delete the dynamically allocated array of player pointers itself.
    delete[] players;

    return 0; // Exit successfully
}

// =====================================================================

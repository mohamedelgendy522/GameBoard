#include"Word_tic_tac_toe.h"
#include "BoardGame_Classes.h"
#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr



    using namespace std;

    int main() {

        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

        // Create an instance of the specific UI for X-O using a pointer 
        UI<char>* game_ui = new Word_UI();

        // Create the game board. For X-O, this is an X_O_Board.
        Board<char>* Word_board = new Word_Board();

        // Use the UI to set up the players for the game.
        // The UI returns a dynamically allocated array of Player pointers.
        Player<char>** players = game_ui->setup_players();

        // Create the game manager with the board and the array of players.
        GameManager<char> Word_game(Word_board, players, game_ui);

        // Run the game loop.
        Word_game.run();

        // --- Cleanup ---
        // Delete the dynamically allocated board object.
        delete Word_board;

        // Delete the individual player objects.
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
        // Delete the dynamically allocated array of player pointers itself.
        delete[] players;

        return 0; // Exit successfully
    }

 

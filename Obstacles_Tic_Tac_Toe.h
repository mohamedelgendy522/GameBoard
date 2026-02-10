/**
 * @file Obstacles_Tic_Tac_Toe.h
 * @brief Defines the Obstacles X-O (Tic-Tac-Toe) specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `Obstacles_XO_Board`: A specialized board class for the Obstacles Tic-Tac-Toe game.
 * - `Obstacles_XO_UI`: A user interface class tailored to Obstacles X-O game setup and player interaction.
 */

#ifndef OBSTACLES_TIC_TAC_TOE_H
#define OBSTACLES_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Obstacles_XO_Board
 * @brief Represents the Obstacles Tic-Tac-Toe game board.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for the Obstacles Tic-Tac-Toe (X-O) game, including
 * move updates, win/draw detection, and display functions.
 *
 * @see Board
 */
class Obstacles_XO_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.
    char obstacles = '#'; ///< Character used to represent an obstacle cell on the board.
public:
    /**
     * @brief Default constructor that initializes a 6x6 Obstacle X-O board.
     */
    Obstacles_XO_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object containing move coordinates and symbol.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the given player has won the game.
     * @param player Pointer to the player being checked.
     * @return true if the player has a winning line, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return Always returns false (not used in Obstacles X-O logic).
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if all cells are filled and no player has won, false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @class Obstacles_XO_UI
 * @brief User Interface class for the Obstacles X-O (Tic-Tac-Toe) game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * Obstacles-X-O–specific functionality for player setup and move input.
 *
 * @see UI
 */
class Obstacles_XO_UI : public UI<char> {
public:
    
    /**
     * @brief Constructs an Obstacles_XO_UI object.
     *
     * Initializes the base `UI<char>` class with the welcome message "Obstacles X-O".
     */
    Obstacles_XO_UI();

    /**
     * @brief Destructor for Obstacles_XO_UI.
     */
    ~Obstacles_XO_UI() {};

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object representing the player's action.
     */
    Move<char>* get_move(Player<char>* player);
};
#endif // OBSTACLES_TIC_TAC_TOE_H


/**
 * @file Numerical_Tic_Tac_Toe.h
 * @brief Defines the Numerical X-O (Tic-Tac-Toe) specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `Numerical_Board`: A specialized board class for the Numerical Tic-Tac-Toe game.
 * - `Numerical_UI`: A user interface class tailored to Numerical X-O game setup and player interaction.
 */

#ifndef NUMERICAL_TIC_TAC_TOE_H
#define NUMERICAL_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
#include <set>
using namespace std;

/**
 * @class Numerical_Board
 * @brief Represents the Numerical Tic-Tac-Toe game board.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for the Numerical Tic-Tac-Toe (X-O) game, including
 * move updates, win/draw detection, and display functions.
 *
 * @see Board
 */
class Numerical_Board : public Board<int> {
private:
    
    set<int> used_numbers; ///< Tracks numbers already played on the board.
public:
    /**
     * @brief Default constructor that initializes a Numerical 3x3 X-O board.
     */
    Numerical_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object containing move coordinates and symbol.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<int>* move);

    /**
     * @brief Checks if the given player has won the game.
     * @param player Pointer to the player being checked.
     * @return true if the player has a winning line, false otherwise.
     */
    bool is_win(Player<int>* player);

    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return Always returns false (not used in Numerical X-O logic).
     */
    bool is_lose(Player<int>*) { return false; };

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if all cells are filled and no player has won, false otherwise.
     */
    bool is_draw(Player<int>* player);

    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<int>* player);
};

/**
 * @class Numerical_UI
 * @brief User Interface class for the Numerical X-O (Tic-Tac-Toe) game.
 *
 * Inherits from the generic `UI<int>` base class and provides
 * Numerical-X-O–specific functionality for player setup and move input.
 *
 * @see UI
 */
class Numerical_UI : public UI<int> {
public:

    /**
     * @brief Constructs an Numerical_UI object.
     *
     * Initializes the base `UI<int>` class with the welcome message "Numerical X-O".
     */
    Numerical_UI();

    /**
     * @brief Destructor for Numerical_UI.
     */
    ~Numerical_UI() {};

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<int> instance.
     */
    Player<int>* create_player(string& name, int symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<int>` object representing the player's action.
     */
    Move<int>* get_move(Player<int>* player);

    /**
     * @brief Sets up the two players for the Numerical X-O game.
     * @return Array of pointers to the created Player<int> objects.
     */
    Player<int>** setup_players();
};
#endif // NUMERICAL_TIC_TAC_TOE_H



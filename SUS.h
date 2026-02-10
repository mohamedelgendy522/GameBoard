/**
 * @file SUS.h
 * @brief Defines the SUS game-specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `SUS_Board`: A specialized board class for the SUS game.
 * - `SUS_UI`: A user interface class tailored to SUS game setup and player interaction.
 */

#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class SUS_Board
 * @brief Represents the SUS game board.
 *
 * Inherits from the generic `Board<char>` class and implements
 * the SUS-specific logic, including move updates, score calculation,
 * win/lose/draw detection, and tracking row/column/diagonal patterns.
 *
 * @see Board
 */
class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

    int score_S = 0; ///< Tracks completed S-U-S patterns for player 'S'.
    int score_U = 0; ///< Tracks completed S-U-S patterns for player 'U'.

    bool main_diagonal_s = false; ///< Tracks if main diagonal had S-related pattern.
    bool main_diagonal_u = false; ///< Tracks if main diagonal had U-related pattern.

    bool anti_diagonal_s = false; ///< Tracks if anti-diagonal had S-related pattern.
    bool anti_diagonal_u = false; ///< Tracks if anti-diagonal had U-related pattern.

    bool row_u[3] = { false,false,false }; ///< Tracks which rows had U pattern.
    bool row_s[3] = { false,false,false }; ///< Tracks which rows had S pattern.

    bool column_u[3] = { false,false,false }; ///< Tracks which columns had U pattern.
    bool column_s[3] = { false,false,false }; ///< Tracks which columns had S pattern.

public:
    /**
     * @brief Default constructor that initializes a 3x3 SUS board.
     */
    SUS_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object containing move coordinates and symbol.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Calculates and updates the scores based on the current board state.
     * @param player Pointer to the player whose patterns are being tracked.
     */
    void update_scores(Player<char>* player);

    /**
     * @brief Checks if the given player has won the game.
     * @param player Pointer to the player being checked.
     * @return true if the player has achieved a winning condition, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return true if the player has a losing condition, false otherwise.
     */
    bool is_lose(Player<char>* player);

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if all cells are filled and no player has won, false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over (win, lose, or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player);
};


/**
 * @class SUS_UI
 * @brief User Interface class for the SUS game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * SUS-specific functionality for player setup and move input.
 *
 * @see UI
 */
class SUS_UI : public UI<char> {
public:
    /**
     * @brief Constructs a SUS_UI object.
     *
     * Initializes the base `UI<char>` class with the welcome message "SUS".
     */
    SUS_UI();

    /**
     * @brief Destructor for SUS_UI.
     */
    ~SUS_UI() {};

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('S' or 'U') assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object representing the player's action.
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Sets up the two players for the SUS game.
     * @return Array of pointers to the created Player<char> objects.
     */
    Player<char>** setup_players();
};

#endif // SUS_H

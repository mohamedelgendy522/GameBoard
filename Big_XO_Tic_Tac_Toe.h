/**
 * @file Big_XO_Tic_Tac_Toe.h
 * @brief Declares classes for the 5×5 Big Tic-Tac-Toe (X-O) game.
 *
 * This header contains:
 * - X_O_Board: Implements move validation, 5×5 grid logic, sequence counting, win/draw detection.
 * - XO_UI: Handles player creation and move input/output for the Big X-O game.
 *
 * These classes extend the generic framework defined in BoardGame_Classes.h.
 */

#ifndef BIG_XO_TIC_TAC_TOE_H
#define BIG_XO_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Big_XO_UI
 * @brief Represents a 5×5 board for the Big X-O Tic-Tac-Toe game.
 *
 * The board:
 * - Uses a 5×5 grid initialized with '.'  
 * - Validates moves  
 * - Counts sequences of identical symbols  
 * - Detects win / draw / end-game states  
 *
 * @see Board
 */
class Big_XO_Board : public Board<char> {
private:
    char blank_symbol = '.';  ///< Symbol used for empty cells

public:

    /**
     * @brief Constructs a new 5×5 Big Tic-Tac-Toe board.
     *
     * Initializes all cells to '.' and resets the move counter.
     */
    Big_XO_Board();

    /**
     * @brief Applies a move to the board if it is valid.
     *
     * A move is rejected if:
     * - It is out of bounds  
     * - The target cell is already occupied  
     *
     * @param move Pointer to a Move<char> object.
     * @return true if applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Counts consecutive symbol sequences on the board.
     *
     * Used for enhanced scoring or advanced win logic.
     *
     * @param sym Symbol to count sequences for.
     * @return Number of found sequences.
     */
    int count_sequences(char sym);

    /**
     * @brief Determines if a player has won.
     *
     * A win occurs when the player has a sequence satisfying
     * the Big X-O win condition (e.g., 4 in a row).
     *
     * @param player Player whose victory is checked.
     * @return true if the player wins.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Always returns false — no loss condition is defined.
     *
     * @return false.
     */
    bool is_lose(Player<char>*) override { return false; }

    /**
     * @brief Detects if the game ended in a draw.
     *
     * A draw occurs when the board is full and no one wins.
     *
     * @param player Unused.
     * @return true if draw.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game is over.
     *
     * The game ends when:
     * - A win occurs  
     * - A draw occurs  
     *
     * @return true if game is finished.
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Displays advanced score information (e.g., sequence counts).
     */
    void display_scores();

    /**
     * @brief Returns number of completed moves.
     */
    int get_n_moves() const { return n_moves; }
};

/**
 * @class Big_XO_UI
 * @brief Handles input/output operations for the Big Tic-Tac-Toe game.
 *
 * Responsibilities:
 * - Creating players  
 * - Requesting user moves  
 * - Supporting human and computer interactions  
 *
 * @see UI
 */
class Big_XO_UI : public UI<char> {
public:

    /**
     * @brief Constructs the UI for the Big Tic-Tac-Toe game.
     */
    Big_XO_UI();

    /**
     * @brief Creates a player of the given type with name and symbol.
     *
     * @param name Player's name.
     * @param symbol Character symbol ('X' or 'O').
     * @param type PlayerType (Human or Computer).
     * @return Pointer to allocated Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Retrieves the next move from a player.
     *
     * - Human players manually enter coordinates  
     * - Computer players generate a move automatically  
     *
     * @param player Pointer to the player making the move.
     * @return Newly allocated Move<char>.
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif

/**
 * @file Word_Classes.h
 * @brief Declares the board and UI classes for the Word Tic-Tac-Toe game.
 *
 * This header contains:
 * - Word_Board: Implements move validation, win logic, draw logic, and board access.
 * - Word_UI: Handles player creation, move input, and board display.
 *
 * These classes extend the generic framework provided in BoardGame_Classes.h.
 */

#ifndef WORD_CLASSES_H
#define WORD_CLASSES_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

/**
 * @class Word_Board
 * @brief Represents a 3×3 board for the Word Tic-Tac-Toe game.
 *
 * The board:
 * - Stores characters placed by players  
 * - Validates moves  
 * - Checks for word completion (win)  
 * - Determines draw and game end conditions  
 *
 * @see Board
 */
class Word_Board : public Board<char> {
public:

    /**
     * @brief Constructs a new Word Board (3×3) initialized with '.'.
     *
     * Also resets the move counter inherited from Board.
     */
    Word_Board();

    /**
     * @brief Applies a player move to the board if valid.
     *
     * Moves are rejected if:
     * - The position is outside the board  
     * - The target cell is already filled  
     *
     * @param move Pointer to a Move<char> object.
     * @return true if the move is valid and applied; false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks whether the board contains a valid word in any row, column, or diagonal.
     *
     * A win occurs when any 3-letter line forms a valid dictionary word.
     *
     * @param player Unused — win does not depend on player symbol.
     * @return true if a winning word is detected.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the game has ended in a draw.
     *
     * A draw occurs when:
     * - All 9 cells are filled, and  
     * - No win condition is met  
     *
     * @return true if the game is a draw.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if the game has ended.
     *
     * The game ends when:
     * - A winning word is found, or  
     * - The board is full (draw)  
     *
     * @return true if the game is over.
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Loss conditions are not used in Word Tic-Tac-Toe.
     *
     * Always returns false unless custom loss rules are added.
     *
     * @return false.
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Retrieves a character from the board.
     *
     * @param x Row index.
     * @param y Column index.
     * @return Character stored at the given position.
     */
    char get_cell(int x, int y) const { return board[x][y]; }
};

/**
 * @class Word_UI
 * @brief Handles player interaction and board display for the Word Game.
 *
 * Responsibilities:
 * - Creating human and computer players  
 * - Taking moves from players  
 * - Printing the board state in a formatted layout  
 *
 * @see UI
 */
class Word_UI : public UI<char> {
public:

    /**
     * @brief Constructs the Word Game UI and initializes its welcome prompt.
     */
    Word_UI();

    /**
     * @brief Creates a player with the given name, symbol, and type.
     *
     * @param name Player name.
     * @param symbol Player's representative character.
     * @param type Human or Computer.
     * @return Pointer to the newly created Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Retrieves the next move entered by a player.
     *
     * - Human players enter (x, y, character) manually.  
     * - Computer players generate a move automatically.  
     *
     * @param player Player whose move is requested.
     * @return Pointer to a newly allocated Move<char>.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Displays the current board contents in a formatted grid.
     *
     * @param board Pointer to the active board.
     */
    void display_board(Board<char>* board);
};

#endif // WORD_CLASSES_H

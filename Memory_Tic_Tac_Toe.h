/**
 * @file Memory_Tic_Tac_Toe.h
 * @brief Defines classes for Memory Tic-Tac-Toe game (Hidden X-O game).
 * @author Dr. El-Ramly
 * @version 2.3
 * @date 2024
 *
 * This file provides:
 * - `Memory_Board`: Board class for Memory Tic-Tac-Toe (hides symbols during display)
 * - `Memory_X_O_UI`: UI class for Memory Tic-Tac-Toe game setup and interaction
 */

#ifndef MEMORY_TIC_TAC_TOE_H
#define MEMORY_TIC_TAC_TOE_H

#include "BoardGame_Classes 2.3v.h"

/**
 * @class Memory_Board
 * @brief Represents the board for Memory Tic-Tac-Toe game.
 * @ingroup MemoryGameClasses
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the classic Tic-Tac-Toe logic but is designed for memory-based gameplay
 * where symbols are hidden during display.
 *
 * @note Board size is fixed at 3x3 (standard Tic-Tac-Toe)
 * @warning Symbols are stored normally but displayed as 'H' (hidden)
 * @see Board
 */
class Memory_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character representing an empty cell

public:
    /**
     * @brief Default constructor that initializes a 3x3 board.
     */
    Memory_Board();
    
    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to Move<char> object containing move coordinates and symbol.
     * @return true if move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move);
    
    /**
     * @brief Checks if player has won (three in a row).
     * @param player Pointer to the player being checked.
     * @return true if player has three consecutive symbols, false otherwise.
     */
    virtual bool is_win(Player<char>* player);
    
    /**
     * @brief Checks if the player has lost (always false in standard X-O).
     * @param player Pointer to the player being checked.
     * @return Always returns false (not used in standard X-O logic).
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
 * @class Memory_X_O_UI
 * @brief User Interface class for Memory Tic-Tac-Toe game.
 * @ingroup MemoryGameClasses
 *
 * Inherits from the generic `UI<char>` base class and provides
 * specific functionality for Memory Tic-Tac-Toe where symbols
 * are displayed as 'H' (hidden) instead of actual 'X' or 'O'.
 *
 * @see UI
 */
class Memory_X_O_UI : public UI<char> {
public:
    /**
     * @brief Constructs a Memory_X_O_UI object.
     */
    Memory_X_O_UI();
    
    /**
     * @brief Destructor for Memory_X_O_UI.
     */
    ~Memory_X_O_UI() {};
    
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
     * @note For human players, prompts for input. For computer players, uses random moves.
     */
    virtual Move<char>* get_move(Player<char>* player);
    
    /**
     * @brief Displays the board matrix with hidden symbols.
     * @param matrix The board matrix to display.
     * @details Displays 'H' instead of actual 'X' or 'O' symbols for memory gameplay.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};

#endif // MEMORY_TIC_TAC_TOE_H
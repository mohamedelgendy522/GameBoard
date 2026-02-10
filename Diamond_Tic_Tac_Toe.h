/**
 * @file DiamondTic_Tac_Toe.h
 * @brief Defines classes for Diamond Tic-Tac-Toe game (X-O with diamond-shaped board).
 * @author Dr. El-Ramly
 * @version 2.3
 * @date 2024
 *
 * This file provides:
 * - `Diamond_X_O_Board`: Board class for Diamond Tic-Tac-Toe (diamond-shaped 10x10 board)
 * - `Diamond_X_O_UI`: UI class for Diamond Tic-Tac-Toe game setup and interaction
 */

#ifndef DIAMOND_TIC_TAC_TOE_H
#define DIAMOND_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>

/**
 * @class Diamond_X_O_Board
 * @brief Represents the board for Diamond Tic-Tac-Toe game.
 * @ingroup DiamondGameClasses
 *
 * This class inherits from the generic `Board<char>` class and implements
 * a diamond-shaped board (10x10 matrix with valid positions forming a diamond).
 * The winning condition requires both a line of 3 and a line of 4 in different directions.
 *
 * @note Board size is 10x10 with only 25 valid positions forming a diamond shape
 * @warning Uses minimax algorithm with depth limitation and alpha-beta pruning
 * @see Board
 */
class Diamond_X_O_Board : public Board<char> {
private:
    char blank_symbol = '_';        ///< Character representing an empty cell
    Player<char>* computer_player;  ///< Pointer to computer player
    Player<char>* human_player;     ///< Pointer to human player
    
    /**
     * @brief Gets all valid (empty) positions on the diamond-shaped board.
     * @return Vector of (x,y) coordinates for valid positions.
     */
    vector<pair<int, int>> get_valid_positions();
    
    /**
     * @brief Counts lines of specific length for a player.
     * @param player Pointer to the player to count lines for.
     * @param length Length of line to count (2, 3, or 4).
     * @return Number of lines of specified length for the player.
     */
    int count_lines(Player<char>* player, int length);

public:
    /**
     * @brief Default constructor that initializes a diamond-shaped 10x10 board.
     * @details Initializes only diamond-shaped positions as playable (25 positions).
     */
    Diamond_X_O_Board();
    
    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to Move<char> object containing move coordinates and symbol.
     * @return true if move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move);
    
    /**
     * @brief Checks if player has won according to diamond game rules.
     * @param player Pointer to the player being checked.
     * @return true if player has at least one line of 3 AND one line of 4 in different directions.
     */
    virtual bool is_win(Player<char>* player);
    
    /**
     * @brief Checks if the player has lost (opponent has won).
     * @param player Pointer to the player being checked.
     * @return true if opponent has won, false otherwise.
     */
    bool is_lose(Player<char>* player);
    
    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if all 25 diamond positions are filled and no player has won.
     */
    bool is_draw(Player<char>* player);
    
    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player);
    
    /**
     * @brief Sets the player pointers for the board.
     * @param comp Pointer to computer player.
     * @param human Pointer to human player.
     */
    void set_players(Player<char>* comp, Player<char>* human);
    
    /**
     * @brief Checks if a position is valid (part of the diamond shape).
     * @param x Row index (0-9).
     * @param y Column index (0-9).
     * @return true if position is playable (not '#' character).
     */
    bool is_valid_position(int x, int y);
    
    /**
     * @brief Checks if the current board state is a terminal state.
     * @return true if game is over (win or all positions filled), false otherwise.
     */
    bool is_terminal();
    
    /**
     * @brief Evaluates the current board state for AI decision making.
     * @return Positive score for computer advantage, negative for human advantage.
     * @details Scores based on: win/lose (+100/-100), lines of 2/3, center control.
     */
    int evaluate();
    
    /**
     * @brief Finds the best move for the computer using minimax algorithm.
     * @return Pointer to the best Move object for the computer.
     * @note Uses depth-limited search (depth=5 by default) for performance.
     */
    Move<char>* find_best_move();
    
    /**
     * @brief Minimax algorithm with alpha-beta pruning and depth limitation.
     * @param is_maximizing true if current player is maximizing (computer), false if minimizing (human).
     * @param alpha Alpha value for alpha-beta pruning.
     * @param beta Beta value for alpha-beta pruning.
     * @param depth Maximum search depth (default 3).
     * @return The evaluated score for the current board state.
     */
    int minimax(bool is_maximizing, int alpha, int beta, int depth = 3);
};

/**
 * @class Diamond_X_O_UI
 * @brief User Interface class for Diamond Tic-Tac-Toe game.
 * @ingroup DiamondGameClasses
 *
 * Inherits from the generic `UI<char>` base class and provides
 * specific functionality for Diamond Tic-Tac-Toe player setup and move input.
 *
 * @see UI
 */
class Diamond_X_O_UI : public UI<char> {
protected:
    Player<char>* player1; ///< Pointer to player 1 (X)
    Player<char>* player2; ///< Pointer to player 2 (O)
    
public:
    /**
     * @brief Constructs a Diamond_X_O_UI object.
     */
    Diamond_X_O_UI();
    
    /**
     * @brief Destructor for Diamond_X_O_UI.
     */
    ~Diamond_X_O_UI() {};
    
    /**
     * @brief Sets up the players for the game.
     * @return Array of two Player pointers (player1 and player2).
     */
    Player<char>** setup_players() override;
    
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
     * @note For human players, prompts for input. For computer players, uses AI.
     */
    virtual Move<char>* get_move(Player<char>* player);
    
    /**
     * @brief Displays the diamond-shaped board matrix.
     * @param matrix The board matrix to display.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const ;
};

#endif // DIAMOND_TIC_TAC_TOE_H
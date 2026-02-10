/**
 * @file Misere_Tic_Tac_Toe.h
 * @brief Defines classes for Misère Tic-Tac-Toe (Inverse X-O) game.
 * @author Dr. El-Ramly
 * @version 2.3
 * @date 2024
 *
 * This file provides:
 * - `Inverse_X_O_Board`: Board class for Misère Tic-Tac-Toe (where losing is the objective)
 * - `Inverse_X_O_UI`: UI class for Misère Tic-Tac-Toe game setup and interaction
 */

#ifndef MISERE_TIC_TAC_TOE_H
#define MISERE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"

/**
 * @class Inverse_X_O_Board
 * @brief Represents the board for Misère Tic-Tac-Toe (Inverse X-O) game.
 * @ingroup InverseGameClasses
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for Misère Tic-Tac-Toe, where the player
 * who makes three in a row LOSES the game.
 *
 * @note Board size is fixed at 3x3
 * @warning Uses minimax algorithm with alpha-beta pruning for AI moves
 * @see Board
 */
class Inverse_X_O_Board : public Board<char> {
private:
    char blank_symbol = '.';     ///< Character representing an empty cell
    Player<char>* computer_player; ///< Pointer to computer player
    Player<char>* human_player;    ///< Pointer to human player

public:
    /**
     * @brief Default constructor that initializes a 3x3 board.
     */
    Inverse_X_O_Board();
    
    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to Move<char> object containing move coordinates and symbol.
     * @return true if move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move);
    
    /**
     * @brief Checks if player has won (always false in Misère).
     * @param player Pointer to the player being checked.
     * @return Always returns false (winning is not checked in Misère).
     * @note In Misère Tic-Tac-Toe, we only check for losing condition.
     */
    virtual bool is_win(Player<char>*) { return false; };
    
    /**
     * @brief Checks if the player has lost (made three in a row).
     * @param player Pointer to the player being checked.
     * @return true if player has three in a row (loses), false otherwise.
     */
    bool is_lose(Player<char>* player);
    
    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if all cells are filled and no player has lost, false otherwise.
     */
    bool is_draw(Player<char>* player);
    
    /**
     * @brief Determines if the game is over (lose or draw).
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
     * @brief Checks if the current board state is a terminal state.
     * @return true if game is over (lose or board full), false otherwise.
     */
    bool is_terminal();
    
    /**
     * @brief Evaluates the current board state for AI decision making.
     * @return Positive score if computer is winning, negative if losing, 0 for draw.
     */
    int evaluate();
    
    /**
     * @brief Finds the best move for the computer using minimax algorithm.
     * @return Pointer to the best Move object for the computer.
     */
    Move<char>* find_best_move();
    
    /**
     * @brief Minimax algorithm with alpha-beta pruning for optimal move selection.
     * @param is_maximizing true if current player is maximizing (computer), false if minimizing (human).
     * @param alpha Alpha value for alpha-beta pruning.
     * @param beta Beta value for alpha-beta pruning.
     * @return The evaluated score for the current board state.
     */
    int minimax(bool is_maximizing, int alpha, int beta);
};

/**
 * @class Inverse_X_O_UI
 * @brief User Interface class for Misère Tic-Tac-Toe game.
 * @ingroup InverseGameClasses
 *
 * Inherits from the generic `UI<char>` base class and provides
 * specific functionality for Misère Tic-Tac-Toe player setup and move input.
 *
 * @see UI
 */
class Inverse_X_O_UI : public UI<char> {
protected:
    Player<char>* player1; ///< Pointer to player 1 (X)
    Player<char>* player2; ///< Pointer to player 2 (O)
    
public:
    /**
     * @brief Constructs an Inverse_X_O_UI object.
     */
    Inverse_X_O_UI();
    
    /**
     * @brief Destructor for Inverse_X_O_UI.
     */
    ~Inverse_X_O_UI() {};
    
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
};

#endif // MISERE_TIC_TAC_TOE_H
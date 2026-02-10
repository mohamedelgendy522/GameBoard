/**
 * @file Four_In_Row.h
 * @brief Defines the Four-In-A-Row specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `FourInRow_Board`: A specialized board class for the Four-In-A-Row game.
 * - `FourInRow_UI`: A user interface class tailored to Four-In-A-Row game setup and player interaction.
 */

#ifndef FOUR_IN_ROW_H
#define FOUR_IN_ROW_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @brief Checks whether a given player symbol achieves a winning 4-in-a-row pattern.
 *
 * @param b   The board matrix.
 * @param sym The player's symbol ('X' or 'O').
 * @return true  If the board contains a winning 4-in-a-row for this symbol.
 * @return false Otherwise.
 */
bool is_winning(const vector<vector<char>>& b, char sym);

/**
 * @brief Detects whether a move creates an immediate 3-in-a-row threat.
 *
 * A "threat" means: 3 symbols + 1 empty cell where gravity allows a winning move.
 *
 * @param b   The board matrix.
 * @param sym The player's symbol.
 * @return true  If the symbol has a valid 3-in-a-row setup.
 * @return false Otherwise.
 */
bool create_threat(const vector<vector<char>>& b, char sym);

/**
 * @brief Gets the lowest available row in a column according to gravity.
 *
 * @param b    The board matrix.
 * @param col  The column index (0–6).
 * @return Row index of the lowest empty cell, or -1 if the column is full.
 */
int get_bottom_most_cell(const vector<vector<char>>& b, int col);

/**
 * @brief Checks whether placing a piece at (r,c) gives the opponent
 *        a dangerous 2-in-a-row extension that should be blocked.
 *
 * This is used by the AI to avoid giving the opponent setups.
 *
 * @param b    The board matrix.
 * @param r    Row of the tested cell.
 * @param c    Column of the tested cell.
 * @param opp  Opponent's symbol.
 * @return true  If this move enables opponent 2-in-a-row.
 * @return false Otherwise.
 */
bool two_in_row(const vector<vector<char>>& b, int r, int c, char opp);


/**
 * @class FourInRow_Board
 * @brief Represents the game board for the Four-In-A-Row game.
 *
 * Inherits from `Board<char>` and overrides its game-specific rules.
 */
class FourInRow_Board : public Board<char> {
private:
    char blank_symbol = '.';  ///< Character used to represent an empty cell on the board.

public:

    /**
     * @brief Default constructor that initializes a 6x7 Four-In-A-Row board.
     */
    FourInRow_Board();

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
     * @return Always returns false (not used in Four-In-A-Row logic).
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
 * @class FourInRow_UI
 * @brief User Interface class for the Four-In-A-Row game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * Four-In-A-Row–specific functionality for player setup and move input.
 *
 * @see UI
 */
class FourInRow_UI : public UI<char> {
public:

    /**
     * @brief Constructs an FourInRow_UI object.
     *
     * Initializes the base `UI<char>` class with the welcome message "Four-In-A-Row".
     */
    FourInRow_UI();

    /**
     * @brief Destructor for FourInRow_UI.
     */
    ~FourInRow_UI() {};

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

#endif // FOUR_IN_ROW_H

/**
 * @file XO_Classes.h
 * @brief Defines the Ultimate X-O (Tic-Tac-Toe) game classes that extend the generic board game framework.
 *
 * This file provides:
 * - `Ultimate`: A specialized 9x9 board class used for the Ultimate Tic-Tac-Toe game.
 * - `Ultimate_UI`: A user interface class tailored for Ultimate X-O player setup and interaction.
 */

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Ultimate
 * @brief Represents the Ultimate Tic-Tac-Toe game board.
 *
 * This class inherits from the generic `Board<char>` and implements
 * the rules of the Ultimate X-O game, including move validation,
 * win/draw detection, and board display logic.
 *
 * @see Board
 */
class Ultimate : public Board<char> {
protected:
    char blank_symbol = '.'; ///< Symbol used to represent an empty cell in the Ultimate board.
public:
    /**
     * @brief Default constructor that initializes a 9x9 Ultimate X-O board.
     */
    Ultimate();

    /**
     * @brief Applies a player's move to the Ultimate X-O board.
     * @param move Pointer to a Move<char> containing coordinates and symbol.
     * @return true if the move is valid and successfully applied; false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the specified player has won the Ultimate X-O game.
     * @param player Pointer to the player being checked.
     * @return true if the player has a winning condition; false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the given player has lost.
     *
     * Not used in Ultimate X-O, always returns false.
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Determines if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if the board is full and no player has won.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Checks if the game is over (win or draw).
     * @param player Pointer to the player being evaluated.
     * @return true if the game has ended; false otherwise.
     */
    bool game_is_over(Player<char>* player);
};


/**
 * @class Ultimate_UI
 * @brief User Interface class for the Ultimate X-O game.
 *
 * Inherits from the generic `UI<char>` and provides functions
 * specific to setting up players and retrieving moves for the
 * Ultimate Tic-Tac-Toe experience.
 *
 * @see UI
 */
class Ultimate_UI : public UI<char> {
public:
    /**
     * @brief Constructs the Ultimate_UI object.
     *
     * Initializes the base UI with the welcome message "Ultimate X-O".
     */
    Ultimate_UI();

    /**
     * @brief Destructor for Ultimate_UI.
     */
    ~Ultimate_UI();

    /**
     * @brief Creates a new player for the Ultimate X-O game.
     * @param name Player name.
     * @param symbol Player's assigned symbol ('X' or 'O').
     * @param type Player type (Human or Computer).
     * @return Pointer to the created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from the given player.
     * @param player Pointer to the player whose move is requested.
     * @return Pointer to a new Move<char> representing the player's intended action.
     */
    virtual Move<char>* get_move(Player<char>* player);
};

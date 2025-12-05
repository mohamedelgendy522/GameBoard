/**
 * @file XO_Classes.h
 * @brief Defines the Shift X-O variant classes that extend the generic board game framework.
 *
 * This file provides:
 * - `X_O_Shift`: A specialized board class implementing the Shift X-O rules.
 * - `X_O_Shift_UI`: A user interface class tailored to Shift X-O player setup and interaction.
 */

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class X_O_Shift
 * @brief Represents the Shift X-O game board.
 *
 * This class inherits from the generic `Board<char>` template and implements
 * the rules of the Shift X-O game, including move updates, shifting behavior,
 * win/draw detection, and board-state management.
 *
 * @see Board
 */
class X_O_Shift : public Board<char> {
protected:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
    /**
     * @brief Default constructor that initializes the 3×3 Shift X-O board.
     */
    X_O_Shift();

    /**
     * @brief Applies a player's move according to Shift X-O rules.
     *
     * In Shift X-O, moves may cause rows or columns to shift depending
     * on the game's mechanics.
     *
     * @param move Pointer to a Move<char> object containing coordinates and symbol.
     * @return true if the move is valid and successfully applied; false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks whether the specified player has achieved a Shift X-O win.
     *
     * A win occurs when the player forms a 3-in-a-row horizontally,
     * vertically, or diagonally after all shifts and updates.
     *
     * @param player Pointer to the player being evaluated.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Always returns false — losing state is not needed in Shift X-O logic.
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Determines whether the Shift X-O game has ended in a draw.
     *
     * A draw occurs when all cells are filled and no winning line exists.
     *
     * @param player Pointer to the player being checked.
     * @return true if the board is full and no player has won.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Checks if the game has ended (either win or draw).
     *
     * @param player Pointer to the player being evaluated.
     * @return true if the game is over; otherwise false.
     */
    bool game_is_over(Player<char>* player);
};


/**
 * @class X_O_Shift_UI
 * @brief User Interface class for the Shift X-O variant.
 *
 * This class inherits from `UI<char>` and provides Shift X-O–specific
 * input handling, player creation, and move acquisition logic.
 *
 * @see UI
 */
class X_O_Shift_UI : public UI<char> {
public:
    /**
     * @brief Constructs the Shift X-O UI.
     *
     * Initializes the base UI with the message:
     * `"Welcome to FCAI Shift X-O"`.
     */
    X_O_Shift_UI();

    /**
     * @brief Destructor.
     */
    ~X_O_Shift_UI() {};

    /**
     * @brief Creates a new player for Shift X-O.
     *
     * @param name    Player's name.
     * @param symbol  Player's mark ('X' or 'O').
     * @param type    Whether the player is Human or Computer.
     * @return Pointer to the newly allocated Player<char>.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     *
     * Human players enter coordinates manually,
     * while computer players generate moves automatically.
     *
     * @param player Pointer to the player whose move is being requested.
     * @return Pointer to a newly created Move<char> representing the action.
     */
    virtual Move<char>* get_move(Player<char>* player);
};

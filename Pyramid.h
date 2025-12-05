/**
 * @file XO_Classes.h
 * @brief Defines the Pyramid X-O game classes that extend the generic board game framework.
 *
 * This file provides:
 * - `Pyramid`: A specialized board class implementing the rules of Pyramid X-O.
 * - `Pyramid_UI`: A user interface class tailored for Pyramid X-O player setup and interaction.
 */

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Pyramid
 * @brief Represents the Pyramid X-O game board.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the logic required for the Pyramid X-O variant, including special move rules,
 * win-condition evaluation, and draw detection.
 *
 * The Pyramid version typically uses a non-standard board arrangement
 * (e.g., triangular or progressively expanding rows), and the class
 * handles all movement validation and game-state updates accordingly.
 *
 * @see Board
 */
class Pyramid : public Board<char> {
protected:
    char blank_symbol = '.'; ///< Character used to represent an empty cell in the Pyramid X-O board.

public:
    /**
     * @brief Default constructor that initializes the Pyramid X-O board.
     *
     * Depending on the game rules, this may initialize a triangular
     * layout or a modified X-O structure instead of a standard 3×3 grid.
     */
    Pyramid();

    /**
     * @brief Updates the board with a player's move according to Pyramid X-O rules.
     *
     * Movement logic differs from normal X-O because valid positions
     * depend on the pyramid structure.
     *
     * @param move Pointer to a Move<char> object containing move coordinates and symbol.
     * @return true if the move is valid and successfully applied; false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks whether the given player has achieved a Pyramid X-O win.
     *
     * Win conditions may include:
     *  - completing a row within the pyramid layers
     *  - completing diagonal edges
     *  - completing the pyramid apex line
     *
     * @param player Pointer to the player being checked.
     * @return true if the player has met any winning condition.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Always returns false — Pyramid X-O does not define player losses explicitly.
     */
    bool is_lose(Player<char>*) { return false; }

    /**
     * @brief Determines whether the game has ended in a draw.
     *
     * A draw occurs when all valid Pyramid X-O positions are filled
     * and no winning condition is met.
     *
     * @param player Pointer to the player being checked.
     * @return true if the board is full and no player has won.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Checks whether the game is over due to win or draw.
     *
     * @param player Pointer to the player being evaluated.
     * @return true if the game is finished; otherwise false.
     */
    bool game_is_over(Player<char>* player);
};


/**
 * @class Pyramid_UI
 * @brief User Interface class for the Pyramid X-O game.
 *
 * This class inherits from `UI<char>` and provides Pyramid-specific
 * player registration, move collection, and display handling.
 *
 * It ensures players follow the spatial constraints of the pyramid layout
 * when selecting moves.
 *
 * @see UI
 */
class Pyramid_UI : public UI<char> {
public:
    /**
     * @brief Constructs a Pyramid_UI object.
     *
     * Initializes the base `UI<char>` class with the welcome message:
     *   "FCAI Pyramid X-O".
     */
    Pyramid_UI();

    /**
     * @brief Destructor for Pyramid_UI.
     */
    ~Pyramid_UI() {};

    /**
     * @brief Creates a player for the Pyramid X-O game.
     *
     * @param name Player name.
     * @param symbol Either 'X' or 'O'.
     * @param type Human or Computer player type.
     * @return Pointer to a newly allocated Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move for the Pyramid X-O game.
     *
     * Human players manually input coordinates;
     * computer players compute valid positions based on the pyramid shape.
     *
     * @param player Pointer to the player providing the move.
     * @return A pointer to a new `Move<char>` instance.
     */
    virtual Move<char>* get_move(Player<char>* player);
};

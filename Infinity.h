/**
 * @file BIG_XO_TIC_TAC_TOE.h
 * @brief Defines the Tic-Tac-Toe board and UI classes.
 *
 * This file provides:
 * - `Infinity_Board`: A board implementation for the Tic-Tac-Toe game.
 * - `Infinity_UI`: The user interface responsible for player creation and move input.
 *
 * Both classes extend the generic framework defined in BoardGame_Classes.h.
 */



#include "BoardGame_Classes.h"
#include <queue>
using namespace std;

/**
 * @class InfinityGame_Board
 * @brief Represents the board used in the Tic-Tac-Toe game.
 *
 * This board stores the X and O symbols placed by players and implements:
 * - Move application logic
 * - Win checking
 * - Draw checking
 * - Game termination conditions
 *
 * A move history queue is also maintained to track the order of moves.
 *
 * @see Board
 */
class InfinityGame_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Symbol representing empty cells.
    queue<pair<int, int>> history; ///< Tracks the order of moves.

public:

    /**
     * @brief Constructs a new Tic-Tac-Toe board.
     *
     * Initializes the board grid and fills all cells with the blank symbol.
     */
    InfinityGame_Board();

    /**
     * @brief Applies a player's move onto the board.
     *
     * A move consists of:
     * - The X (row) coordinate
     * - The Y (column) coordinate
     * - The player's symbol (X or O)
     *
     * @param move Pointer to a Move<char> containing the player's action.
     * @return true if the move is valid and applied successfully, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks whether the specified player has won the game.
     *
     * A player wins by completing a full row, column, or diagonal
     * with their symbol.
     *
     * @param player The player being evaluated.
     * @return true if the player meets the winning condition, false otherwise.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks whether the player has lost.
     *
     * Loss is not defined in standard Tic-Tac-Toe,
     * so this always returns false.
     *
     * @param player The player to evaluate.
     * @return false Always.
     */
    bool is_lose(Player<char>*) override { return false; }

    /**
     * @brief Checks whether the game ended in a draw.
     *
     * A draw occurs when the board is full and neither player has won.
     *
     * @param player The player being checked (not directly used).
     * @return true if the game is a draw, false otherwise.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if the game is over.
     *
     * The game ends when:
     * - A player wins
     * - Or the board is full (draw)
     *
     * @param player Player used to check the game state.
     * @return true if the game has finished, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class InfinityGame_UI
 * @brief User Interface class for the Tic-Tac-Toe game.
 *
 * Responsible for:
 * - Player creation
 * - Collecting player moves
 * - Displaying the game board
 *
 * @see UI
 */
class InfinityGame_UI : public UI<char> {
public:

    /**
     * @brief Constructs the user interface for Tic-Tac-Toe.
     *
     * Displays a welcome message or initializes UI components.
     */
    InfinityGame_UI();

    /**
     * @brief Creates a new player (Human or Computer).
     *
     * Assigns:
     * - Player name
     * - Symbol (X or O)
     * - Type (Human / Computer)
     *
     * @param name Player name.
     * @param symbol Player symbol.
     * @param type Player type.
     * @return Pointer to a new Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Retrieves the next move from the player.
     *
     * Prompts the player to enter the coordinates of the move.
     *
     * @param player Pointer to the player whose move is requested.
     * @return Pointer to a new Move<char> object.
     */
    Move<char>* get_move(Player<char>* player) override;
};



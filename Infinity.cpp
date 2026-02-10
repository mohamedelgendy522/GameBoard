#include <iostream>
#include <iomanip>
#include <cctype>
#include "Infinity.h"

using namespace std;

// ============================================================================
//                              X_O_Board Implementation
// ============================================================================

/**
 * @brief Constructs a 3x3 Infinity Tic-Tac-Toe board and initializes it with blank symbols.
 */
InfinityGame_Board::InfinityGame_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

/**
 * @brief Updates the board with a move. Supports placing, undoing, and "infinite" rules.
 *
 * Rules:
 * - Human/computer places a symbol in an empty cell
 * - Every 3rd move, oldest move is removed (infinite mode)
 * - Undo a move if symbol is 0
 *
 * @param move Pointer to the Move object with coordinates and symbol.
 * @return True if the move was successfully applied, false otherwise.
 */
bool InfinityGame_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = toupper(move->get_symbol());

    // Bounds check
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "\n Invalid move! Position (" << x << ", " << y << ") is outside the board.\n";
        return false;
    }

    // Cell occupancy
    if (board[x][y] != blank_symbol) {
        cout << "\n Invalid move! Cell (" << x << ", " << y << ") is already filled.\n";
        return false;
    }

    // Undo move
    if (mark == 0) {
        if (board[x][y] == blank_symbol) return false;

        board[x][y] = blank_symbol;
        n_moves = max(0, n_moves - 1);

        queue<pair<int, int>> newq;
        while (!history.empty()) {
            auto p = history.front(); history.pop();
            if (!(p.first == x && p.second == y)) newq.push(p);
        }
        history = std::move(newq);
        return true;
    }

    // Infinite mode: remove oldest move every 3rd move
    static int moveCounter = 0;
    moveCounter++;

    if (moveCounter % 3 == 0 && !history.empty()) {
        auto oldest = history.front();
        history.pop();
        int ox = oldest.first;
        int oy = oldest.second;

        if (board[ox][oy] != blank_symbol) {
            board[ox][oy] = blank_symbol;
            n_moves = std::max(0, n_moves - 1);
        }
    }

    board[x][y] = mark;
    n_moves++;
    history.push({ x, y });

    return true;
}

/**
 * @brief Checks if the specified player has won.
 *
 * Win is determined by a full row, column, or diagonal of the player's symbol.
 *
 * @param player Pointer to the player.
 * @return True if the player wins, false otherwise.
 */
bool InfinityGame_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    auto eq = [&](char a, char b, char c) {
        return (a == sym && b == sym && c == sym);
        };

    // Rows and Columns
    for (int i = 0; i < 3; i++) {
        if (eq(board[i][0], board[i][1], board[i][2])) return true;
        if (eq(board[0][i], board[1][i], board[2][i])) return true;
    }

    // Diagonals
    if (eq(board[0][0], board[1][1], board[2][2])) return true;
    if (eq(board[0][2], board[1][1], board[2][0])) return true;

    return false;
}

/**
 * @brief Draw condition for Infinity Tic-Tac-Toe is not used.
 *
 * @param player Pointer to player (not used)
 * @return Always false.
 */
bool InfinityGame_Board::is_draw(Player<char>* player) {
    return false;
}

/**
 * @brief Determines if the game is over.
 *
 * Game ends if a player wins.
 *
 * @param player Pointer to current player.
 * @return True if the game has ended.
 */
bool InfinityGame_Board::game_is_over(Player<char>* player) {
    return is_win(player);
}

// ============================================================================
//                              XO_UI Implementation
// ============================================================================

/**
 * @brief Constructs the Infinity Tic-Tac-Toe UI with welcome message.
 */
InfinityGame_UI::InfinityGame_UI() : UI<char>("Welcome to Infinity Tic-Tac-Toe (3x3)", 2) {}

/**
 * @brief Creates a player (Human or Computer) for the game.
 *
 * @param name Player name.
 * @param symbol Player's symbol.
 * @param type PlayerType (HUMAN or COMPUTER)
 * @return Pointer to the newly created Player object.
 */
Player<char>* InfinityGame_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating "
        << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

/**
 * @brief Retrieves the next move from the player.
 *
 * Human: prompts input (x, y)
 * Computer: generates random coordinates.
 *
 * @param player Pointer to the current player.
 * @return Pointer to a Move object.
 */
Move<char>* InfinityGame_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name()
            << " (" << player->get_symbol()
            << ") enter your move x y (0 to 2): ";
        cin >> x >> y;
    }
    else {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }

    return new Move<char>(x, y, player->get_symbol());
}

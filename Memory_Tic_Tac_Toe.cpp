/**
 * @file Memory_Tic_Tac_Toe.cpp
 * @brief Implementation of Memory Tic-Tac-Toe classes.
 * @author Dr. El-Ramly
 * @version 2.3
 * @date 2024
 *
 * This file contains the implementation of:
 * - Memory_Board class methods
 * - Memory_X_O_UI class methods
 */

#include "Memory_Tic_Tac_Toe.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

//--------------------------------------- Memory_Board Implementation

/**
 * @brief Constructs a Memory_Board with 3x3 dimensions.
 * @details Initializes all cells with the blank symbol ('.').
 * @see Memory_Board::Memory_Board
 */
Memory_Board::Memory_Board() : Board(3,3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

/**
 * @brief Updates the board with a move.
 * @param move Pointer to Move object containing coordinates and symbol.
 * @return true if move was valid and applied, false otherwise.
 * @see Memory_Board::update_board
 */
bool Memory_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {         // Apply move
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
        }
    return false;
}

/**
 * @brief Checks if player has won (three in a row).
 * @param player Pointer to the player to check.
 * @return true if player has three consecutive symbols, false otherwise.
 * @see Memory_Board::is_win
 */
bool Memory_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
    };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }

    // Check diagonals
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

/**
 * @brief Checks if game is a draw.
 * @param player Pointer to the player (unused, for interface compatibility).
 * @return true if board is full and no player has won, false otherwise.
 * @see Memory_Board::is_draw
 */
bool Memory_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

/**
 * @brief Checks if game is over.
 * @param player Pointer to the player.
 * @return true if game is won or drawn, false otherwise.
 * @see Memory_Board::game_is_over
 */
bool Memory_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- Memory_X_O_UI Implementation

/**
 * @brief Constructs a Memory_X_O_UI object.
 * @see Memory_X_O_UI::Memory_X_O_UI
 */
Memory_X_O_UI::Memory_X_O_UI() : UI<char>("Weclome to FCAI Memory X-O Game", 3) {}

/**
 * @brief Creates a player with specified attributes.
 * @param name Player name.
 * @param symbol Player symbol ('X' or 'O').
 * @param type Player type (Human or Computer).
 * @return Pointer to created Player object.
 * @see Memory_X_O_UI::create_player
 */
Player<char>* Memory_X_O_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets move from player (human input or computer random move).
 * @param player Pointer to player requesting move.
 * @return Pointer to Move object representing the selected move.
 * @note Computer moves are random, human moves require manual input.
 * @see Memory_X_O_UI::get_move
 */
Move<char>* Memory_X_O_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}

/**
 * @brief Displays the board matrix with hidden symbols.
 * @param matrix The board matrix to display.
 * @details Displays 'H' instead of actual 'X' or 'O' symbols to implement memory gameplay.
 *          Blank cells are shown as '.' and other characters are displayed normally.
 * @see Memory_X_O_UI::display_board_matrix
 */
void Memory_X_O_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    if (matrix.empty() || matrix[0].empty()) return;

    int rows = matrix.size();
    int cols = matrix[0].size();

    cout << "\n    ";
    for (int j = 0; j < cols; ++j)
        cout << setw(cell_width + 1) << j;
    cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";

    for (int i = 0; i < rows; ++i) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 'X' || matrix[i][j] == 'O')
                cout << setw(cell_width) << 'H' << " |";
            else
                cout << setw(cell_width) << matrix[i][j] << " |";
        }
        cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
    }
    cout << endl;
}
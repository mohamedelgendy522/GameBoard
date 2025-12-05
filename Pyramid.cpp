#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "Pyramid.h"
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief A map used to mark which board positions are valid playable cells
 *        in the Pyramid X-O structure.
 *
 * Valid cells = true
 * Blocked/invalid cells = false
 *
 * Example:
 *   - Levels 0–2 are blocked: '#'
 *   - Level 3: middle 3 cells playable
 *   - Level 4: all 5 cells playable
 */
map<pair<int,int>,bool> check;

/**
 * @brief Constructor initializes the Pyramid-shaped X-O board (5×5).
 *
 * Pyramid Layout:
 *   Row 0: #####
 *   Row 1: #####
 *   Row 2: ##.##
 *   Row 3: #...#
 *   Row 4: .....
 *
 * '#' = blocked (non-playable)
 * '.' = empty playable cell
 *
 * `check` map marks all playable positions.
 */
Pyramid::Pyramid() : Board(5, 5) {
    // Block all upper 3 rows initially
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j] = '#';
        }
    }

    // Middle apex of pyramid
    board[2][2] = '.';
    check[{2,2}] = true;

    // Second row from bottom
    for (int i = 1; i < 4; i++) {
        board[3][i] = '.';
        check[{3,i}] = true;
    }

    // Bottom base of the pyramid
    for (int i = 0; i < 5; i++) {
        check[{4,i}] = true;
        board[4][i] = '.';
    }
}

/**
 * @brief Applies a player's move if the selected coordinate is valid
 *        and inside the pyramid shape.
 *
 * A valid move requires:
 *   - Cell is marked playable in `check`
 *   - Cell contains `.`
 *
 * @param move Pointer to Move<char> containing (x,y) and symbol.
 * @return true if move is allowed and placed; false otherwise.
 */
bool Pyramid::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Cell must be a valid pyramid coordinate AND empty
    if (!check[{x,y}] || board[x][y] != '.') {
        return false;
    }

    // Place the player's symbol
    board[x][y] = mark;
    return true;
}

/**
 * @brief Checks whether the player has achieved any Pyramid X-O winning pattern.
 *
 * Win Conditions include:
 *   ✓ Left diagonal      (4,0) → (3,1) → (2,2)
 *   ✓ Right diagonal     (4,4) → (3,3) → (2,2)
 *   ✓ Vertical middle    (4,2) → (3,2) → (2,2)
 *   ✓ Middle row         (3,1) (3,2) (3,3)
 *   ✓ Any 3-in-a-row on bottom row (4,0–2), (4,1–3), (4,2–4)
 *
 * @param player The player to check.
 * @return true if a winning pattern is found.
 */
bool Pyramid::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
    };

    // Diagonal checks
    if ((all_equal(board[4][0],board[3][1],board[2][2]) && board[4][0] == sym)
        || (all_equal(board[4][4],board[3][3],board[2][2]) && board[4][4] == sym))
        return true;

    // Vertical
    if (all_equal(board[4][2],board[3][2],board[2][2]) && board[4][2] == sym)
        return true;

    // Middle horizontal in row 3
    if (all_equal(board[3][1],board[3][2],board[3][3]) && board[3][3] == sym)
        return true;

    // Any 3-in-a-row on bottom row
    for (int i = 0 ; i < 3; i++) {
        if (all_equal(board[4][i],board[4][i + 1],board[4][i + 2]) && board[4][i] == sym)
            return true;
    }

    return false;
}

/**
 * @brief Determines whether the game ended in a draw.
 *
 * Draw happens when:
 *   - n_moves reaches 9 (the number of playable cells)
 *   - No player has achieved a win
 *
 * @param player The player being checked (not used except for win-check).
 * @return true if draw; false otherwise.
 */
bool Pyramid::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

/**
 * @brief Determines if the game is finished by win or draw.
 */
bool Pyramid::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//-------------------------------------------------------------
//                    Pyramid_UI Implementation
//-------------------------------------------------------------

/**
 * @brief Initializes the UI with a welcome message for Pyramid X-O.
 */
Pyramid_UI::Pyramid_UI()
    : UI<char>("Weclome to Pyramid X-O Game ", 3) {}

/**
 * @brief Creates a player (Human or Computer) for Pyramid X-O.
 */
Player<char>* Pyramid_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating "
         << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

/**
 * @brief Retrieves the next move from the player.
 *
 * Human:
 *   - Inputs x & y manually.
 *
 * Computer:
 *   - Scans the board for the first available playable '.' cell
 *     according to the pyramid shape.
 *
 * @param player Pointer to the player making a move.
 * @return A new Move<char> representing the player's action.
 */
Move<char>* Pyramid_UI::get_move(Player<char>* player) {
    int x, y;

    // Human selects coordinates
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y";
        cin >> x >> y;
    }
    // Computer selects first available valid cell
    else if (player->get_type() == PlayerType::COMPUTER) {
        Board<char>* b = player->get_board_ptr();

        for (int i = 0; i < b->get_rows(); i++) {
            for (int j = 0; j < b->get_columns(); j++) {

                if (check[{i, j}] && b->get_cell(i, j) == '.') {
                    return new Move<char>(i, j, player->get_symbol());
                }
            }
        }
    }

    return new Move<char>(x, y, player->get_symbol());
}
